#include "level_factory_system.hpp"

#include <fstream>  // ifstream
#include <ios>      // ios

#include "components/ctx/level_size.hpp"
#include "components/ctx/viewport.hpp"
#include "components/humanoid_state.hpp"
#include "core/algorithms.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/serialization.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/graphics/depth_system.hpp"
#include "systems/graphics/drawable_system.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/humanoid/humanoid_factory_system.hpp"
#include "systems/saves/registry_serialization_system.hpp"

namespace wanderer::sys {
namespace {

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
  for (const auto& ts : data.tilesets)
  {
    graphics.load(ts.sheet.id, ts.sheet.path);
  }
}

[[nodiscard]] auto load_tilemap(entt::registry& registry,
                                const comp::tilemap::entity entity,
                                const ir::level& data) -> map_id
{
  auto& tilemap = registry.emplace<comp::tilemap>(entity);

  tilemap.id = map_id{data.id};
  tilemap.row_count = data.row_count;
  tilemap.col_count = data.col_count;
  tilemap.size = data.size;
  tilemap.humanoid_layer = data.humanoid_layer;

  return tilemap.id;
}

void make_tiles(entt::registry& registry,
                comp::tileset& tileset,
                const graphics_context& graphics,
                const std::map<tile_id, ir::tile>& tiles)
{
  for (const auto& [id, tileData] : tiles)
  {
    const auto tileEntity = comp::tile::entity{registry.create()};
    tileset.tiles.try_emplace(id, tileEntity);

    auto& tile = registry.emplace<comp::tile>(tileEntity);
    tile.id = id;
    tile.texture = graphics.to_index(tileData.texture);
    tile.src = tileData.source;

    if (tileData.fancy)
    {
      const auto& fancy = *tileData.fancy;
      tile.depth = fancy.depth;

      if (fancy.animation)
      {
        registry.emplace<comp::tile_animation>(tileEntity, *fancy.animation);
      }
    }
  }
}

void load_tileset(entt::registry& registry,
                  const comp::tileset::entity entity,
                  const graphics_context& graphics,
                  const std::vector<ir::tileset>& data)
{
  auto& tileset = registry.emplace<comp::tileset>(entity);

  tileset.tiles.reserve(accumulate(data, [](const ir::tileset& tileset) {
    return tileset.tiles.size();
  }));

  for (const auto& ts : data)
  {
    make_tiles(registry, tileset, graphics, ts.tiles);
  }
}

void add_ground_layers(entt::registry& registry, const ir::level& data)
{
  for (const auto& groundLayer : data.ground_layers)
  {
    auto& layer = registry.emplace<comp::tile_layer>(registry.create(), groundLayer);
    layer.matrix.shrink_to_fit();
  }

  registry.sort<comp::tile_layer>(
      [](const comp::tile_layer& lhs, const comp::tile_layer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

void insert_hitbox(aabb_tree& tree, const entt::entity entity, const comp::hitbox& hitbox)
{
  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

[[nodiscard]] auto convert(const ir::depth_drawable& drawable,
                           const graphics_context& graphics) -> comp::depth_drawable
{
  comp::depth_drawable result;

  result.texture = graphics.to_index(drawable.texture);
  result.depth = drawable.depth;
  result.dst = drawable.dst;
  result.src = drawable.src;
  result.layer = drawable.layer;

  return result;
}

void add_tile_objects(comp::level& level,
                      const graphics_context& graphics,
                      const ir::level& levelData)
{
  const auto& tileset = level.registry.get<comp::tileset>(level.tileset);

  for (const auto& objectData : levelData.tile_objects)
  {
    const auto entity = comp::tile_object::entity{level.registry.create()};

    auto& tileObject = level.registry.emplace<comp::tile_object>(entity);
    tileObject.tile_entity = tileset.tiles.at(objectData.tile);

    level.registry.emplace<comp::depth_drawable>(entity,
                                                 convert(objectData.drawable, graphics));

    if (objectData.hitbox)
    {
      const auto& hitbox =
          level.registry.emplace<comp::hitbox>(entity, *objectData.hitbox);
      insert_hitbox(level.tree, entity, hitbox);
    }

    if (const auto* animation =
            level.registry.try_get<comp::tile_animation>(tileObject.tile_entity))
    {
      level.registry.emplace<comp::tile_animation>(entity, *animation);
    }
  }
}

[[nodiscard]] auto find_inventory(entt::registry& registry, const int id)
    -> maybe<comp::inventory::entity>
{
  maybe<comp::inventory::entity> result;

  for (auto&& [entity, inventory, object] :
       registry.view<comp::inventory, comp::object>().each())
  {
    if (object.id == id)
    {
      result.emplace(entity);
    }
  }

  return result;
}

void set_up_container_triggers(entt::registry& registry)
{
  for (auto&& [entity, trigger] : registry.view<comp::container_trigger>().each())
  {
    if (const auto result = find_inventory(registry, trigger.inventory_id))
    {
      trigger.inventory_entity = comp::inventory::entity{*result};
    }
  }
}

void add_objects(entt::registry& registry, const ir::level& level)
{
  for (const auto& data : level.objects)
  {
    const auto entity = comp::object::entity{registry.create()};

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable)
    {
      registry.emplace<comp::depth_drawable>(entity, *data.drawable);
    }

    if (data.hitbox)
    {
      registry.emplace<comp::hitbox>(entity, *data.hitbox);
    }

    if (data.portal)
    {
      registry.emplace<comp::portal>(entity, *data.portal);
    }

    if (data.inventory)
    {
      registry.emplace<comp::inventory>(entity, *data.inventory);
    }

    if (data.inventory_ref)
    {
      auto& trigger = registry.emplace<comp::container_trigger>(entity);
      trigger.inventory_id = *data.inventory_ref;
      trigger.inventory_entity = null<comp::inventory>();  // Set up later
    }

    if (data.spawnpoint)
    {
      registry.emplace<comp::spawnpoint>(entity, *data.spawnpoint);
    }

    if (data.light)
    {
      registry.emplace<comp::point_light>(entity, *data.light);
    }
  }

  set_up_container_triggers(registry);
}

void spawn_humanoids(comp::level& level, graphics_context& graphics)
{
  // The player has to be created before other humanoids!
  sys::make_player(level.registry,
                   level.tree,
                   level.player_spawn_position.value(),
                   graphics);

  for (auto&& [entity, spawnpoint] : level.registry.view<comp::spawnpoint>().each())
  {
    switch (spawnpoint.type)
    {
      case comp::spawnpoint_type::player:
        break;

      case comp::spawnpoint_type::skeleton: {
        sys::make_skeleton(level.registry, level.tree, spawnpoint.position, graphics);
        break;
      }
    }
  }
}

void add_level_size(entt::registry& registry, comp::level& level)
{
  const auto& tilemap = registry.get<comp::tilemap>(level.tilemap);
  auto& size = registry.set<ctx::level_size>();
  size.row_count = tilemap.row_count;
  size.col_count = tilemap.col_count;
}

void add_viewport(entt::registry& registry, comp::level& level)
{
  const auto& tilemap = registry.get<comp::tilemap>(level.tilemap);
  registry.set<ctx::viewport>(sys::make_viewport(tilemap.size));
}

}  // namespace

auto make_level(const ir::level& data, graphics_context& graphics) -> comp::level
{
  load_tileset_textures(data, graphics);

  comp::level level;

  level.tree.disable_thickness_factor();
  level.registry = make_registry();
  level.player_spawn_position = data.player_spawn_point;

  auto& registry = level.registry;
  level.tilemap = comp::tilemap::entity{registry.create()};
  level.tileset = comp::tileset::entity{registry.create()};

  load_tileset(registry, level.tileset, graphics, data.tilesets);
  level.id = load_tilemap(registry, level.tilemap, data);

  add_level_size(registry, level);
  add_viewport(registry, level);
  add_ground_layers(registry, data);
  add_tile_objects(level, graphics, data);
  add_objects(registry, data);

  spawn_humanoids(level, graphics);

  {
    const auto& tilemap = registry.get<comp::tilemap>(level.tilemap);
    for (auto&& [entity, drawable] :
         registry.view<comp::depth_drawable, comp::humanoid>().each())
    {
      drawable.layer = tilemap.humanoid_layer;
    }
  }

  sys::center_viewport_on(registry, level.player_spawn_position.value());
  sys::update_drawables(registry);
  sys::update_depth(registry);

  level.tree.rebuild();

  return level;
}

auto make_level(const std::filesystem::path& path, graphics_context& graphics)
    -> comp::level
{
  comp::level level;

  std::ifstream stream{path, std::ios::binary};
  input_archive archive{stream};

  // Do not change order!
  level.registry = sys::restore_registry(archive);
  archive(level.tree);
  archive(level.tilemap);
  archive(level.player_spawn_position);

  add_level_size(level.registry, level);
  add_viewport(level.registry, level);

  return level;
}

}  // namespace wanderer::sys
