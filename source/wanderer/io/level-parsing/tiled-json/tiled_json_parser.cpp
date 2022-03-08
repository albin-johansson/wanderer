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
#include "wanderer/data/direction.hpp"
#include "wanderer/io/json.hpp"
#include "wanderer/meta/profile.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"
#include "wanderer/systems/animation_system.hpp"
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

void _create_player(entt::registry& registry,
                    graphics_ctx& graphics,
                    const glm::vec2& position,
                    const GameConfig& cfg)
{
  const auto playerEntity = registry.create();
  registry.emplace<comp::Player>(playerEntity);
  registry.emplace<comp::Humanoid>(playerEntity);

  auto& object = registry.emplace<comp::GameObject>(playerEntity);
  object.position = position;
  object.size = cfg.humanoid_draw_size;

  registry.emplace<comp::ViewportTarget>(playerEntity);

  auto& light = registry.emplace<comp::PointLight>(playerEntity);
  light.offset = cfg.humanoid_draw_size / 2.0f;
  light.fluctuation = 0;
  light.step_size = 0;
  light.limit = 0;
  light.size = cfg.humanoid_draw_size.x;

  sys::add_physics_body(registry,
                        playerEntity,
                        b2_dynamicBody,
                        object.position,
                        object.size / 2.0f,
                        5,
                        {object.size.x / 4.0f, object.size.y / 4.0f});

  const auto& map = registry.ctx<comp::Tilemap>();

  auto& drawable = registry.emplace<comp::Drawable>(playerEntity);
  drawable.texture = graphics.load_texture("resources/images/player.png");
  drawable.layer_index = map.humanoid_layer_index;
  drawable.depth_index = 4;  // TODO
  drawable.src.set_size(64, 64);

  registry.emplace<comp::Animation>(playerEntity);

  auto& seq = registry.emplace<comp::SeqAnimation>(playerEntity);
  seq.frame_size = {64, 64};

  sys::enter_humanoid_idle_animation(registry, playerEntity, direction_down_bit);
}

}  // namespace

auto parse_tiled_json_map(const std::filesystem::path& path,
                          graphics_ctx& graphics,
                          const GameConfig& cfg) -> entt::registry
{
  WANDERER_PROFILE_START

  auto json = read_json(path);
  _verify_features(json);

  auto registry = sys::make_level_registry(cfg);

  auto& map = registry.ctx<comp::Tilemap>();
  json.at("height").get_to(map.row_count);
  json.at("width").get_to(map.col_count);

  map.size.x = static_cast<float32>(map.col_count) * cfg.tile_size.x;
  map.size.y = static_cast<float32>(map.row_count) * cfg.tile_size.y;

  map.humanoid_layer_index = tiled::get_property<int32>(json, "humanoid-layer");

  auto& viewport = registry.ctx<comp::Viewport>();
  viewport.keep_in_bounds = tiled::get_property<bool>(json, "is-outside");

  const auto dir = path.parent_path();

  for (const auto& [_, tilesetJson] : json.at("tilesets").items()) {
    tiled::parse_tileset(tilesetJson, dir, registry, graphics);
  }

  const auto mapTileWidth = json.at("tilewidth").get<float32>();
  const auto mapTileHeight = json.at("tileheight").get<float32>();
  const auto tileSizeRatio = cfg.tile_size / glm::vec2{mapTileWidth, mapTileHeight};

  for (int32 z = 0; const auto& [_, layerJson] : json.at("layers").items()) {
    tiled::parse_layer(layerJson, registry, z, tileSizeRatio);
    ++z;
  }

  /* Make sure that tile layers are stored in the intended order for rendering */
  registry.storage<comp::TileLayer>().sort(
      [&](const entt::entity a, const entt::entity b) {
        const auto& left = registry.get<comp::TileLayer>(a);
        const auto& right = registry.get<comp::TileLayer>(b);
        return left.z < right.z;
      });

  for (auto&& [entity, object, spawn] :
       registry.view<comp::GameObject, comp::SpawnPoint>().each()) {
    if (spawn.mob == MobType::player) {
      _create_player(registry, graphics, object.position, cfg);
    }
  }

  sys::sort_drawables(registry, sys::sort_strategy::std);

  WANDERER_PROFILE_END("Parsed Tiled JSON map")
  return registry;
}

}  // namespace wanderer::io