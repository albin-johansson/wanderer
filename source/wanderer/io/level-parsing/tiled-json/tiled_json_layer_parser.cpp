#include "tiled_json_layer_parser.hpp"

#include <string>  // string

#include "tiled_json_utils.hpp"
#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/systems/physics_system.hpp"

namespace wanderer::io::tiled {
namespace {

void _parse_tile_objects(const nlohmann::json& json,
                         entt::registry& registry,
                         const int32 z)
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

    const auto& info = registry.get<comp::tile_info>(tileObject.tile_entity);

    auto& gameObject = registry.emplace<comp::game_object>(entity);
    gameObject.position = {static_cast<float32>(col) * cfg.tile_size.x,
                           static_cast<float32>(row) * cfg.tile_size.y};
    gameObject.size = cfg.tile_size;

    auto& drawable = registry.emplace<comp::drawable>(entity);
    drawable.texture = info.texture;
    drawable.src = as_rect(info.source);
    drawable.layer_index = z;
    drawable.depth_index = info.depth_index;

    if (const auto* hitbox =
            registry.try_get<comp::tile_hitbox>(tileObject.tile_entity)) {
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
  const auto& map = registry.ctx<comp::tilemap>();

  if (tiled::get_property<bool>(json, "is-ground")) {
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
    _parse_tile_objects(json, registry, z);
  }
}

void _parse_object_layer(const nlohmann::json& json,
                         entt::registry& registry,
                         const int32 z)
{
  // TODO
}

}  // namespace

void parse_layer(const nlohmann::json& json, entt::registry& registry, const int32 z)
{
  const auto type = json.at("type").get<std::string>();

  if (type == "tilelayer") {
    _parse_tile_layer(json, registry, z);
  }
  else if (type == "objectgroup") {
    _parse_object_layer(json, registry, z);
  }
  else if (type == "group") {
    // TODO
  }
}

}  // namespace wanderer::io::tiled