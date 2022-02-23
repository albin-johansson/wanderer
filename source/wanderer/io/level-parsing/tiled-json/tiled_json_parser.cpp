#include "tiled_json_parser.hpp"

#include <string>       // string
#include <string_view>  // string_view

#include "wanderer/core/graphics.hpp"
#include "wanderer/core/math.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tags.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/io/json.hpp"
#include "wanderer/meta/profile.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"
#include "wanderer/systems/physics_system.hpp"
#include "wanderer/systems/registry_system.hpp"

namespace wanderer {
namespace {

template <typename T>
[[nodiscard]] auto _get_property(const nlohmann::json& json,
                                 const std::string_view property)
{
  if (const auto props = json.find("properties"); props != json.end()) {
    for (const auto& [key, object] : props->items()) {
      if (property == object.at("name")) {
        return object.at("value").get<T>();
      }
    }
  }

  throw_traced(wanderer_error{"Did not find property!"});
}

void _verify_features(const nlohmann::json& json)
{
  if (const auto iter = json.find("infinite");
      iter != json.end() && iter.value() != false) {
    throw_traced(wanderer_error{"Invalid infinite map!"});
  }

  if (json.at("orientation") != "orthogonal") {
    throw_traced(wanderer_error{"Only orthogonal maps are supported!"});
  }

  // TODO version
}

void _parse_tileset_tiles_metadata(const nlohmann::json& tilesetJson,
                                   entt::registry& registry,
                                   const tile_id first,
                                   const glm::vec2& tileSizeRatio)
{
  const auto& tileset = registry.ctx<comp::tileset>();

  for (const auto& [_, tileJson] : tilesetJson.at("tiles").items()) {
    const auto localId = tileJson.at("id").get<tile_id>();
    const auto globalId = first + localId;

    const auto tileEntity = tileset.tiles.at(globalId);

    if (tileJson.contains("animation")) {
      auto& animation = registry.emplace<comp::animation>(tileEntity);
      auto& tileAnimation = registry.emplace<comp::tile_animation>(tileEntity);

      const auto arr = tileJson.at("animation");
      animation.frame_count = arr.size();

      animation.delays.reserve(animation.frame_count);
      tileAnimation.frames.reserve(animation.frame_count);

      for (const auto& [frameKey, frameJson] : arr.items()) {
        const auto tile = first + frameJson.at("tileid").get<tile_id>();
        const auto duration = frameJson.at("duration").get<uint64>();

        tileAnimation.frames.push_back(tile);
        animation.delays.emplace_back(duration);
      }
    }

    if (tileJson.contains("objectgroup")) {
      const auto& objects = tileJson.at("objectgroup").at("objects");

      if (objects.size() != 1) {
        throw_traced(wanderer_error{"Tiles must only feature one object!"});
      }

      const auto& objectJson = objects.at(0);

      auto& hitbox = registry.emplace<comp::tile_hitbox>(tileEntity);
      hitbox.offset.x = objectJson.at("x").get<float32>() * tileSizeRatio.x;
      hitbox.offset.y = objectJson.at("y").get<float32>() * tileSizeRatio.y;
      hitbox.size.x = objectJson.at("width").get<float32>() * tileSizeRatio.x;
      hitbox.size.y = objectJson.at("height").get<float32>() * tileSizeRatio.y;
    }
  }
}

void _parse_common_tileset_attributes(const nlohmann::json& json,
                                      const std::filesystem::path& dir,
                                      const tile_id firstId,
                                      entt::registry& registry,
                                      graphics_ctx& graphics)
{
  auto& tileset = registry.ctx<comp::tileset>();

  const auto tileWidth = json.at("tilewidth").get<int32>();
  const auto tileHeight = json.at("tileheight").get<int32>();
  const auto columns = json.at("columns").get<int32>();

  const auto imagePath = dir / json.at("image").get<std::string>();
  const auto textureId = graphics.load_texture(imagePath);

  const auto count = json.at("tilecount").get<tile_id>();
  const auto end = firstId + count;

  tileset.tiles.reserve(tileset.tiles.bucket_count() + count);

  int32 index = 0;
  for (tile_id id = firstId; id < end; ++id, ++index) {
    const auto entity = registry.create();
    tileset.tiles[id] = entity;

    auto& info = registry.emplace<comp::tile_info>(entity);
    info.texture = textureId;
    info.depth_index = 5;  // TODO

    const auto row = index / columns;
    const auto col = index % columns;

    info.source.x = col * tileWidth;
    info.source.y = row * tileHeight;
    info.source.z = tileWidth;
    info.source.w = tileHeight;
  }

  if (json.contains("tiles")) {
    const auto& cfg = registry.ctx<game_cfg>();
    const auto tileSizeRatio = cfg.tile_size / glm::vec2{tileWidth, tileHeight};

    _parse_tileset_tiles_metadata(json, registry, firstId, tileSizeRatio);
  }
}

void _parse_tileset(const nlohmann::json& json,
                    const std::filesystem::path& dir,
                    entt::registry& registry,
                    graphics_ctx& graphics)
{
  const auto firstTile = json.at("firstgid");
  if (json.contains("source")) {
    const auto path = dir / json.at("source");
    const auto external = read_json(path);
    _parse_common_tileset_attributes(external, dir, firstTile, registry, graphics);
  }
  else {
    _parse_common_tileset_attributes(json, dir, firstTile, registry, graphics);
  }
}

void _parse_tile_objects(const nlohmann::json& json, entt::registry& registry)
{
  const auto& map = registry.ctx<comp::tilemap>();
  const auto& cfg = registry.ctx<game_cfg>();

  auto& tileset = registry.ctx<comp::tileset>();

  usize index = 0;
  for (const auto& [_, value] : json.at("data").items()) {
    const auto tile = value.get<tile_id>();

    if (tile == empty_tile) {
      ++index;
      continue;
    }

    const auto row = index / map.col_count;
    const auto col = index % map.col_count;

    const auto entity = registry.create();

    auto& tileObject = registry.emplace<comp::tile_object>(entity);
    tileObject.tile_entity = tileset.tiles.at(tile);

    auto& gameObject = registry.emplace<comp::game_object>(entity);
    gameObject.position = {static_cast<float32>(col) * cfg.tile_size.x,
                           static_cast<float32>(row) * cfg.tile_size.y};
    gameObject.size = cfg.tile_size;

    if (const auto* hitbox =
            registry.try_get<comp::tile_hitbox>(tileObject.tile_entity)) {
      sys::add_physics_body(registry,
                            entity,
                            b2_staticBody,
                            gameObject.position + hitbox->offset,
                            hitbox->size,
                            0);
    }

    ++index;
  }
}

void _parse_tile_layer(const nlohmann::json& json,
                       entt::registry& registry,
                       const int32 z)
{
  const auto& map = registry.ctx<comp::tilemap>();

  if (_get_property<bool>(json, "is-ground")) {
    using tile_matrix = comp::tile_layer::tile_matrix;
    using tile_row = comp::tile_layer::tile_row;

    const auto entity = registry.create();
    auto& layer = registry.emplace<comp::tile_layer>(entity);
    layer.tiles = tile_matrix(map.row_count, tile_row(map.col_count, empty_tile));
    layer.z = z;

    usize index = 0;
    for (const auto& [_, value] : json.at("data").items()) {
      const auto tile = value.get<tile_id>();

      const auto row = index / map.col_count;
      const auto col = index % map.col_count;
      layer.tiles[row][col] = tile;

      ++index;
    }
  }
  else {
    _parse_tile_objects(json, registry);
  }
}

void _parse_layer(const nlohmann::json& json, entt::registry& registry, const int32 z)
{
  const auto type = json.at("type").get<std::string>();

  if (type == "tilelayer") {
    _parse_tile_layer(json, registry, z);
  }
  else if (type == "objectgroup") {
    // TODO
  }
  else if (type == "group") {
    // TODO
  }
}

void _create_player(entt::registry& registry, const game_cfg& cfg)
{
  const auto playerEntity = registry.create();
  registry.emplace<comp::player>(playerEntity);

  auto& object = registry.emplace<comp::game_object>(playerEntity);
  object.position = {2'800, 3'500};
  object.size = cfg.humanoid_draw_size;

  registry.emplace<comp::viewport_target>(playerEntity);

  sys::add_physics_body(registry,
                        playerEntity,
                        b2_dynamicBody,
                        object.position,
                        object.size,
                        5);
}

}  // namespace

auto parse_tiled_json_map(const std::filesystem::path& path,
                          graphics_ctx& graphics,
                          const game_cfg& cfg) -> entt::registry
{
  WANDERER_PROFILE_START

  auto json = read_json(path);
  _verify_features(json);

  auto registry = sys::make_level_registry(cfg);

  auto& map = registry.ctx<comp::tilemap>();
  json.at("height").get_to(map.row_count);
  json.at("width").get_to(map.col_count);

  map.size.x = static_cast<float32>(map.col_count) * cfg.tile_size.x;
  map.size.y = static_cast<float32>(map.row_count) * cfg.tile_size.y;

  map.humanoid_layer_index = 5;  // TODO read property

  const auto dir = path.parent_path();

  for (const auto& [_, tilesetJson] : json.at("tilesets").items()) {
    _parse_tileset(tilesetJson, dir, registry, graphics);
  }

  for (int32 z = 0; const auto& [_, layerJson] : json.at("layers").items()) {
    _parse_layer(layerJson, registry, z);
    ++z;
  }

  /* Make sure that tile layers are stored in the intended order for rendering */
  registry.storage<comp::tile_layer>().sort(
      [&](const entt::entity a, const entt::entity b) {
        const auto& left = registry.get<comp::tile_layer>(a);
        const auto& right = registry.get<comp::tile_layer>(b);
        return left.z < right.z;
      });

  _create_player(registry, cfg);

  WANDERER_PROFILE_END("Parsed Tiled JSON map")
  return registry;
}

}  // namespace wanderer