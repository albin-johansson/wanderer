#include "tiled_json_parser.hpp"

#include "tiled_json_layer_parser.hpp"
#include "tiled_json_tileset_parser.hpp"
#include "tiled_json_utils.hpp"
#include "wanderer/core/centurion_utils.hpp"
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
#include "wanderer/systems/rendering_system.hpp"

namespace wanderer::io {
namespace {

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

  map.humanoid_layer_index = tiled::get_property<int32>(json, "humanoid-layer");

  auto& viewport = registry.ctx<comp::viewport>();
  viewport.keep_in_bounds = tiled::get_property<bool>(json, "is-outside");

  const auto dir = path.parent_path();

  for (const auto& [_, tilesetJson] : json.at("tilesets").items()) {
    tiled::parse_tileset(tilesetJson, dir, registry, graphics);
  }

  for (int32 z = 0; const auto& [_, layerJson] : json.at("layers").items()) {
    tiled::parse_layer(layerJson, registry, z);
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

  sys::sort_drawables(registry, sys::sort_strategy::std);

  WANDERER_PROFILE_END("Parsed Tiled JSON map")
  return registry;
}

}  // namespace wanderer::io