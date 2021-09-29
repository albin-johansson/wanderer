#include "restore_level_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert
#include <centurion.hpp>

#include "components/ai/chase.hpp"
#include "components/ai/humanoid.hpp"
#include "components/ai/roam.hpp"
#include "components/associated_entity.hpp"
#include "components/gfx/animated.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/physics/float3.hpp"
#include "components/physics/hitbox.hpp"
#include "components/physics/movable.hpp"
#include "components/physics/particle.hpp"
#include "components/plant.hpp"
#include "components/player.hpp"
#include "components/tiles/tile.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "components/trigger.hpp"
#include "core/ecs/make_registry.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto restore(const protobuf::float2& data) -> float2
{
  float2 result;
  result.x = data.x();
  result.y = data.y();
  return result;
}

[[nodiscard]] auto restore(const protobuf::float3& data) -> comp::float3
{
  comp::float3 result;
  result.x = data.x();
  result.y = data.y();
  result.z = data.z();
  return result;
}

[[nodiscard]] auto restore(const protobuf::irect& data) -> cen::irect
{
  cen::irect result;
  result.set_x(data.x());
  result.set_y(data.y());
  result.set_width(data.width());
  result.set_height(data.height());
  return result;
}

[[nodiscard]] auto restore(const protobuf::frect& data) -> cen::frect
{
  cen::frect result;
  result.set_x(data.x());
  result.set_y(data.y());
  result.set_width(data.width());
  result.set_height(data.height());
  return result;
}

[[nodiscard]] auto restore(const protobuf::farea& data) -> cen::farea
{
  cen::farea result;
  result.width = data.width();
  result.height = data.height();
  return result;
}

[[nodiscard]] auto restore(const protobuf::color& data) -> cen::color
{
  cen::color result;
  result.set_red(static_cast<uint8>(data.red()));
  result.set_green(static_cast<uint8>(data.green()));
  result.set_blue(static_cast<uint8>(data.blue()));
  result.set_alpha(static_cast<uint8>(data.alpha()));
  return result;
}

void restore_movable(const protobuf::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& movables = level.movables();
  if (const auto it = movables.find(entt::to_integral(entity)); it != movables.end()) {
    const auto& data = it->second;

    auto& movable = registry.emplace<comp::movable>(entity);
    movable.position = restore(data.position());
    movable.velocity = restore(data.velocity());
    movable.speed = data.speed();
  }
}

void restore_drawable(const protobuf::level& level,
                      entt::registry& registry,
                      const entt::entity entity)
{
  const auto& drawables = level.drawables();
  if (const auto it = drawables.find(entt::to_integral(entity)); it != drawables.end()) {
    const auto& data = it->second;

    auto& drawable = registry.emplace<comp::depth_drawable>(entity);
    drawable.texture = texture_index{data.texture_index()};
    drawable.layer = data.layer_index();
    drawable.depth = data.depth_index();
    drawable.src = restore(data.src());
    drawable.dst = restore(data.dst());
  }
}

void restore_animation(const protobuf::level& level,
                       entt::registry& registry,
                       const entt::entity entity)
{
  const auto& animations = level.animations();
  if (const auto it = animations.find(entt::to_integral(entity)); it != animations.end())
  {
    const auto& data = it->second;

    auto& animation = registry.emplace<comp::animated>(entity);
    animation.frame = data.frame();
    animation.frame_count = data.frame_count();
    animation.delay = ms_t{data.delay()};
    animation.then = ms_t{data.then()};
  }
}

void restore_plant(const protobuf::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& plants = level.plants();
  if (const auto it = plants.find(entt::to_integral(entity)); it != plants.end()) {
    const auto& data = it->second;

    auto& plant = registry.emplace<comp::plant>(entity);
    plant.current = data.current_growth();
    plant.rate = data.rate();
    plant.base_y = data.base_y();
    plant.tile_height = data.tile_height();
    plant.index = data.index();

    for (const auto id : data.tiles()) {
      plant.tiles.emplace_back(id);
    }

    for (const auto id : data.tall_tiles()) {
      plant.tall.emplace_back(id);
    }
  }
}

void restore_tile(const protobuf::level& level,
                  entt::registry& registry,
                  const entt::entity entity)
{
  const auto& tiles = level.tiles();
  if (const auto it = tiles.find(entt::to_integral(entity)); it != tiles.end()) {
    const auto& data = it->second;

    auto& tile = registry.emplace<comp::tile>(entity);
    tile.id = tile_id{data.id()};
    tile.texture = texture_index{data.texture_index()};
    tile.depth = data.depth_index();
    tile.src = restore(data.src());
  }
}

void restore_tilemap(const protobuf::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& tilemaps = level.tilemaps();
  if (const auto it = tilemaps.find(entt::to_integral(entity)); it != tilemaps.end()) {
    const auto& data = it->second;

    auto& tilemap = registry.emplace<comp::tilemap>(entity);
    tilemap.id = map_id{data.id()};
    tilemap.humanoid_layer = data.humanoid_layer_index();
    tilemap.size = restore(data.size());
    tilemap.row_count = data.row_count();
    tilemap.col_count = data.column_count();
  }
}

void restore_tile_animations(const protobuf::level& level,
                             entt::registry& registry,
                             const entt::entity entity)
{
  const auto& animations = level.tile_animations();
  if (const auto it = animations.find(entt::to_integral(entity)); it != animations.end())
  {
    const auto& data = it->second;

    auto& animation = registry.emplace<comp::tile_animation>(entity);
    animation.index = data.index();
    animation.then = ms_t{data.then()};

    for (const auto& frameData : data.frames()) {
      auto& frame = animation.frames.emplace_back();
      frame.tile = tile_id{frameData.tile_id()};
      frame.duration = ms_t{frameData.duration()};
    }
  }
}

void restore_chase(const protobuf::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& chases = level.chases();
  if (const auto it = chases.find(entt::to_integral(entity)); it != chases.end()) {
    const auto& data = it->second;
    assert(registry.valid(entt::entity{data.target_entity()}));

    auto& chase = registry.emplace<comp::chase>(entity);
    chase.target = entt::entity{data.target_entity()};
    chase.range = data.range();
    chase.active = data.is_active();
  }
}

void restore_particle(const protobuf::level& level,
                      entt::registry& registry,
                      const entt::entity entity)
{
  const auto& particles = level.particles();
  if (const auto it = particles.find(entt::to_integral(entity)); it != particles.end()) {
    const auto& data = it->second;

    auto& particle = registry.emplace<comp::particle>(entity);
    particle.position = restore(data.position());
    particle.acceleration = restore(data.acceleration());
    particle.now = data.now();
    particle.duration = data.duration();
    particle.color = restore(data.color());
  }
}

void restore_light(const protobuf::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& lights = level.lights();
  if (const auto it = lights.find(entt::to_integral(entity)); it != lights.end()) {
    const auto& data = it->second;

    auto& light = registry.emplace<comp::point_light>(entity);
    light.position = restore(data.position());
    light.size = data.size();
    light.fluctuation = data.fluctuation();
    light.fluctuation_step = data.fluctuation_step();
    light.fluctuation_limit = data.fluctuation_limit();
  }
}

void restore_spawnpoint(const protobuf::level& level,
                        entt::registry& registry,
                        const entt::entity entity)
{
  const auto& spawnpoints = level.spawnpoints();
  if (const auto it = spawnpoints.find(entt::to_integral(entity));
      it != spawnpoints.end()) {
    const auto& data = it->second;

    auto& spawnpoint = registry.emplace<comp::spawnpoint>(entity);
    spawnpoint.type = static_cast<comp::spawnpoint_type>(data.type());
    spawnpoint.position = restore(data.position());
  }
}

void restore_hitbox(const protobuf::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& hitboxes = level.hitboxes();
  if (const auto it = hitboxes.find(entt::to_integral(entity)); it != hitboxes.end()) {
    const auto& data = it->second;

    auto& hitbox = registry.emplace<comp::hitbox>(entity);
    hitbox.origin = restore(data.origin());
    hitbox.bounds = restore(data.bounds());
    hitbox.enabled = data.enabled();

    for (const auto& boxData : data.boxes()) {
      auto& box = hitbox.boxes.emplace_back();
      box.offset = restore(boxData.offset());
      box.size = restore(boxData.size());
    }
  }
}

void restore_object(const protobuf::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& objects = level.objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id();
  }
}

void restore_portal(const protobuf::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& portals = level.portals();
  if (const auto it = portals.find(entt::to_integral(entity)); it != portals.end()) {
    const auto& data = it->second;

    auto& portal = registry.emplace<comp::portal>(entity);
    portal.path = data.path();
    if (data.has_map_id()) {
      portal.target = map_id{data.map_id()};
    }
  }
}

void restore_tile_layer(const protobuf::level& level,
                        entt::registry& registry,
                        const entt::entity entity)
{
  const auto& layers = level.tile_layers();
  if (const auto it = layers.find(entt::to_integral(entity)); it != layers.end()) {
    const auto& data = it->second;

    auto& layer = registry.emplace<comp::tile_layer>(entity);
    layer.z = data.z_index();

    const auto& matrix = data.matrix();
    for (const auto& rowData : matrix.rows()) {
      auto& row = layer.matrix.emplace_back();
      for (const auto tile : rowData.tiles()) {
        row.emplace_back(tile);
      }
    }
  }
}

void restore_tileset(const protobuf::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& tilesets = level.tilesets();
  if (const auto it = tilesets.find(entt::to_integral(entity)); it != tilesets.end()) {
    const auto& data = it->second;

    auto& tileset = registry.emplace<comp::tileset>(entity);
    for (const auto& [id, tileEntity] : data.tile_to_entity()) {
      tileset.tiles.try_emplace(tile_id{id}, entt::entity{tileEntity});
    }
  }
}

void restore_inventory(const protobuf::level& level,
                       entt::registry& registry,
                       const entt::entity entity)
{
  const auto& inventories = level.inventories();
  if (const auto it = inventories.find(entt::to_integral(entity));
      it != inventories.end()) {
    const auto& data = it->second;

    auto& inventory = registry.emplace<comp::inventory>(entity);
    inventory.capacity = data.capacity();

    for (const auto itemEntity : data.items()) {
      inventory.items.emplace_back(entt::entity{itemEntity});
    }
  }
}

void restore_tile_object(const protobuf::level& level,
                         entt::registry& registry,
                         const entt::entity entity)
{
  const auto& objects = level.tile_objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;

    auto& object = registry.emplace<comp::tile_object>(entity);
    object.tile_entity = entt::entity{data.tile_entity()};
  }
}

void restore_trigger(const protobuf::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& triggers = level.triggers();
  if (const auto it = triggers.find(entt::to_integral(entity)); it != triggers.end()) {
    const auto& data = it->second;

    auto& trigger = registry.emplace<comp::trigger>(entity);
    trigger.type = static_cast<comp::trigger_type>(data.type());
  }
}

void restore_association(const protobuf::level& level,
                         entt::registry& registry,
                         const entt::entity entity)
{
  const auto& associations = level.associations();
  if (const auto it = associations.find(entt::to_integral(entity));
      it != associations.end())
  {
    const auto& data = it->second;

    auto& association = registry.emplace<comp::associated_entity>(entity);
    association.entity = entt::entity{data.entity()};
  }
}

}  // namespace

auto restore_level_registry(const protobuf::level& data) -> entt::registry
{
  auto registry = make_registry();

  const auto playerEntity = entt::entity{data.player_entity()};

  for (const auto id : data.entities()) {
    const auto hint = entt::entity{id};
    const auto entity = registry.create(hint);
    assert(entity == hint);

    if (entity == playerEntity) {
      assert(registry.empty<comp::player>());
      registry.emplace<comp::player>(entity);
    }

    restore_movable(data, registry, entity);
    restore_drawable(data, registry, entity);
    restore_animation(data, registry, entity);
    restore_plant(data, registry, entity);
    restore_tile(data, registry, entity);
    restore_tilemap(data, registry, entity);
    restore_tile_animations(data, registry, entity);
    restore_particle(data, registry, entity);
    restore_light(data, registry, entity);
    restore_spawnpoint(data, registry, entity);
    restore_hitbox(data, registry, entity);
    restore_object(data, registry, entity);
    restore_portal(data, registry, entity);
    restore_tile_layer(data, registry, entity);
    restore_tileset(data, registry, entity);
    restore_inventory(data, registry, entity);
    restore_tile_object(data, registry, entity);
    restore_trigger(data, registry, entity);
    restore_association(data, registry, entity);
  }

  /* We need to ensure that all entities are created when restoring these components */
  for (const auto id : data.entities()) {
    restore_chase(data, registry, entt::entity{id});
  }

  for (const auto id : data.humanoids()) {
    const auto entity = entt::entity{id};
    assert(registry.valid(entity));

    registry.emplace<comp::humanoid_idle>(entity);
    registry.emplace<comp::humanoid>(entity);
  }

  return registry;
}

}  // namespace wanderer
