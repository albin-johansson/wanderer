#include "tiled_json_layer_parser.hpp"

#include <string>  // string

#include "tiled_json_utils.hpp"
#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/logging.hpp"
#include "wanderer/systems/physics_system.hpp"

namespace wanderer::io::tiled {
namespace {

void _parse_tile_objects(const nlohmann::json& json,
                         entt::registry& registry,
                         const int32 z)
{
  const auto& map = registry.ctx().at<comp::Tilemap>();
  const auto& cfg = registry.ctx().at<GameConfig>();

  auto& tileset = registry.ctx().at<comp::Tileset>();

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

    auto& tileObject = registry.emplace<comp::TileObject>(entity);
    tileObject.tile_entity = tileset.tiles.at(tile);

    const auto& info = registry.get<comp::TileInfo>(tileObject.tile_entity);

    auto& gameObject = registry.emplace<comp::GameObject>(entity);
    gameObject.position = {static_cast<float32>(col) * cfg.tile_size.x,
                           static_cast<float32>(row) * cfg.tile_size.y};
    gameObject.size = cfg.tile_size;

    auto& drawable = registry.emplace<comp::Drawable>(entity);
    drawable.texture = info.texture;
    drawable.src = as_rect(info.source);
    drawable.layer_index = z;
    drawable.depth_index = info.depth_index;

    if (const auto* hitbox = registry.try_get<comp::TileHitbox>(tileObject.tile_entity)) {
      sys::add_physics_body(registry,
                            entity,
                            b2_staticBody,
                            gameObject.position,
                            hitbox->size,
                            0,
                            hitbox->offset);
    }

    ++index;
  }
}

void _parse_tile_layer(const nlohmann::json& json,
                       entt::registry& registry,
                       const int32 z)
{
  const auto& map = registry.ctx().at<comp::Tilemap>();

  if (tiled::get_property<bool>(json, "is-ground")) {
    using tile_matrix = comp::TileLayer::tile_matrix;
    using tile_row = comp::TileLayer::tile_row;

    const auto entity = registry.create();
    auto& layer = registry.emplace<comp::TileLayer>(entity);
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
    _parse_tile_objects(json, registry, z);
  }
}

void _parse_light(const nlohmann::json& json,
                  entt::registry& registry,
                  const entt::entity entity,
                  const glm::vec2& tileSizeRatio)
{
  auto& light = registry.emplace<comp::PointLight>(entity);

  light.size = json.at("width").get<float32>() * tileSizeRatio.x;
  light.offset.x = light.size / 2.0f;
  light.offset.y = light.size / 2.0f;

  light.fluctuation = 0;
  light.step_size = 1;
  light.limit = 5;

  light.limit = get_property<float32>(json, "limit", light.limit);
  light.step_size = get_property<float32>(json, "step", light.step_size);
}

void _parse_object_layer(const nlohmann::json& json,
                         entt::registry& registry,
                         const glm::vec2& tileSizeRatio)
{
  for (const auto& [_, objectJson] : json.at("objects").items()) {
    const auto entity = registry.create();

    auto& object = registry.emplace<comp::GameObject>(entity);
    object.position.x = objectJson.at("x").get<float32>() * tileSizeRatio.x;
    object.position.y = objectJson.at("y").get<float32>() * tileSizeRatio.y;

    object.size.x = objectJson.at("width").get<float32>() * tileSizeRatio.x;
    object.size.y = objectJson.at("height").get<float32>() * tileSizeRatio.y;

    const auto tag = objectJson.at("type").get<std::string>();
    if (tag == "Light") {
      _parse_light(objectJson, registry, entity, tileSizeRatio);
    }
    else if (tag == "Spawnpoint") {
      auto& spawn = registry.emplace<comp::SpawnPoint>(entity);
      spawn.mob = MobType::player;  // TODO parse mob type
    }

    // TODO
  }
}

}  // namespace

void parse_layer(const nlohmann::json& json,
                 entt::registry& registry,
                 const int32 z,
                 const glm::vec2& tileSizeRatio)
{
  const auto type = json.at("type").get<std::string>();

  if (type == "tilelayer") {
    _parse_tile_layer(json, registry, z);
  }
  else if (type == "objectgroup") {
    _parse_object_layer(json, registry, tileSizeRatio);
  }
  else if (type == "group") {
    // TODO
  }
}

}  // namespace wanderer::io::tiled