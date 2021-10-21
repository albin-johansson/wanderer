#include "restore_data.hpp"

#include <cassert>  // assert

#include <save.pb.h>

#include "common/texture_index.hpp"
#include "components/ai/chase.hpp"
#include "components/associated_entity.hpp"
#include "components/gfx/animation.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/physics/hitbox.hpp"
#include "components/physics/movable.hpp"
#include "components/physics/particle.hpp"
#include "components/plant.hpp"
#include "components/tiles/tile.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "components/trigger.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

auto restore(const proto::float2& data) -> float2
{
  assert(data.has_x());
  assert(data.has_y());

  float2 result;
  result.x = data.x();
  result.y = data.y();
  return result;
}

auto restore(const proto::float3& data) -> comp::Vector3
{
  assert(data.has_x());
  assert(data.has_y());
  assert(data.has_z());

  comp::Vector3 result;
  result.x = data.x();
  result.y = data.y();
  result.z = data.z();
  return result;
}

auto restore(const proto::irect& data) -> cen::irect
{
  assert(data.has_x());
  assert(data.has_y());
  assert(data.has_width());
  assert(data.has_height());

  cen::irect result;

  result.set_x(data.x());
  result.set_y(data.y());
  result.set_width(data.width());
  result.set_height(data.height());

  return result;
}

auto restore(const proto::frect& data) -> cen::frect
{
  assert(data.has_x());
  assert(data.has_y());
  assert(data.has_width());
  assert(data.has_height());

  cen::frect result;

  result.set_x(data.x());
  result.set_y(data.y());
  result.set_width(data.width());
  result.set_height(data.height());

  return result;
}

auto restore(const proto::farea& data) -> cen::farea
{
  assert(data.has_width());
  assert(data.has_height());

  cen::farea result;

  result.width = data.width();
  result.height = data.height();

  return result;
}

auto restore(const proto::color& data) -> cen::color
{
  assert(data.has_red());
  assert(data.has_green());
  assert(data.has_blue());
  assert(data.has_alpha());

  cen::color result;

  result.set_red(static_cast<uint8>(data.red()));
  result.set_green(static_cast<uint8>(data.green()));
  result.set_blue(static_cast<uint8>(data.blue()));
  result.set_alpha(static_cast<uint8>(data.alpha()));

  return result;
}

auto restore(const proto::time_of_day& data) -> ctx::TimeOfDay
{
  assert(data.has_hour());
  assert(data.has_minute());
  assert(data.has_seconds());
  assert(data.has_week());
  assert(data.has_day());
  assert(data.has_tint());

  ctx::TimeOfDay time;

  time.hour = data.hour();
  time.minute = data.minute();
  time.seconds = data.seconds();
  time.week = data.week();
  time.day = static_cast<DayOfWeek>(data.day());
  time.tint = restore(data.tint());

  return time;
}

void restore_movable(const proto::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& movables = level.movables();
  if (const auto it = movables.find(entt::to_integral(entity)); it != movables.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_velocity());
    assert(data.has_speed());

    auto& movable = registry.emplace<comp::Movable>(entity);
    movable.position = restore(data.position());
    movable.velocity = restore(data.velocity());
    movable.speed = data.speed();
  }
}

void restore_drawable(const proto::level& level,
                      entt::registry& registry,
                      const entt::entity entity)
{
  const auto& drawables = level.drawables();
  if (const auto it = drawables.find(entt::to_integral(entity)); it != drawables.end()) {
    const auto& data = it->second;
    assert(data.has_texture_index());
    assert(data.has_layer_index());
    assert(data.has_depth_index());
    assert(data.has_src());
    assert(data.has_dst());

    auto& drawable = registry.emplace<comp::Drawable>(entity);
    drawable.texture = texture_index{data.texture_index()};
    drawable.layer = data.layer_index();
    drawable.depth = data.depth_index();
    drawable.src = restore(data.src());
    drawable.dst = restore(data.dst());
  }
}

void restore_animation(const proto::level& level,
                       entt::registry& registry,
                       const entt::entity entity)
{
  const auto& animations = level.animations();
  if (const auto it = animations.find(entt::to_integral(entity)); it != animations.end())
  {
    const auto& data = it->second;
    assert(data.has_frame());
    assert(data.has_frame_count());
    assert(data.has_delay());
    assert(data.has_then());

    auto& animation = registry.emplace<comp::Animation>(entity);
    animation.frame = data.frame();
    animation.frame_count = data.frame_count();
    animation.delay = ms_t{data.delay()};
    animation.then = ms_t{data.then()};
  }
}

void restore_plant(const proto::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& plants = level.plants();
  if (const auto it = plants.find(entt::to_integral(entity)); it != plants.end()) {
    const auto& data = it->second;
    assert(data.has_current_growth());
    assert(data.has_rate());
    assert(data.has_base_y());
    assert(data.has_tile_height());
    assert(data.has_index());

    auto& plant = registry.emplace<comp::Plant>(entity);
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

void restore_tile(const proto::level& level,
                  entt::registry& registry,
                  const entt::entity entity)
{
  const auto& tiles = level.tiles();
  if (const auto it = tiles.find(entt::to_integral(entity)); it != tiles.end()) {
    const auto& data = it->second;
    assert(data.has_id());
    assert(data.has_texture_index());
    assert(data.has_depth_index());
    assert(data.has_src());

    auto& tile = registry.emplace<comp::Tile>(entity);
    tile.id = tile_id{data.id()};
    tile.texture = texture_index{data.texture_index()};
    tile.depth = data.depth_index();
    tile.src = restore(data.src());
  }
}

void restore_tilemap(const proto::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& tilemaps = level.tilemaps();
  if (const auto it = tilemaps.find(entt::to_integral(entity)); it != tilemaps.end()) {
    const auto& data = it->second;
    assert(data.has_id());
    assert(data.has_humanoid_layer_index());
    assert(data.has_size());
    assert(data.has_row_count());
    assert(data.has_column_count());

    auto& tilemap = registry.emplace<comp::Tilemap>(entity);
    tilemap.id = map_id{data.id()};
    tilemap.humanoid_layer = data.humanoid_layer_index();
    tilemap.size = restore(data.size());
    tilemap.row_count = data.row_count();
    tilemap.col_count = data.column_count();
  }
}

void restore_tile_animations(const proto::level& level,
                             entt::registry& registry,
                             const entt::entity entity)
{
  const auto& animations = level.tile_animations();
  if (const auto it = animations.find(entt::to_integral(entity)); it != animations.end())
  {
    const auto& data = it->second;
    assert(data.has_index());
    assert(data.has_then());

    auto& animation = registry.emplace<comp::TileAnimation>(entity);
    animation.index = data.index();
    animation.then = ms_t{data.then()};

    for (const auto& frameData : data.frames()) {
      assert(frameData.has_tile_id());
      assert(frameData.has_duration());

      auto& frame = animation.frames.emplace_back();
      frame.tile = tile_id{frameData.tile_id()};
      frame.duration = ms_t{frameData.duration()};
    }
  }
}

void restore_chase(const proto::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& chases = level.chases();
  if (const auto it = chases.find(entt::to_integral(entity)); it != chases.end()) {
    const auto& data = it->second;
    assert(data.has_target_entity());
    assert(data.has_range());
    assert(data.has_is_active());

    const auto targetEntity = entt::entity{data.target_entity()};
    assert(registry.valid(targetEntity));

    auto& chase = registry.emplace<comp::Chase>(entity);
    chase.target = targetEntity;
    chase.range = data.range();
    chase.active = data.is_active();
  }
}

void restore_particle(const proto::level& level,
                      entt::registry& registry,
                      const entt::entity entity)
{
  const auto& particles = level.particles();
  if (const auto it = particles.find(entt::to_integral(entity)); it != particles.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_acceleration());
    assert(data.has_now());
    assert(data.has_duration());
    assert(data.has_color());

    auto& particle = registry.emplace<comp::particle>(entity);
    particle.position = restore(data.position());
    particle.acceleration = restore(data.acceleration());
    particle.now = data.now();
    particle.duration = data.duration();
    particle.color = restore(data.color());
  }
}

void restore_light(const proto::level& level,
                   entt::registry& registry,
                   const entt::entity entity)
{
  const auto& lights = level.lights();
  if (const auto it = lights.find(entt::to_integral(entity)); it != lights.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_size());
    assert(data.has_fluctuation());
    assert(data.has_fluctuation_step());
    assert(data.has_fluctuation_limit());

    auto& light = registry.emplace<comp::PointLight>(entity);
    light.position = restore(data.position());
    light.size = data.size();
    light.fluctuation = data.fluctuation();
    light.fluctuation_step = data.fluctuation_step();
    light.fluctuation_limit = data.fluctuation_limit();
  }
}

void restore_spawnpoint(const proto::level& level,
                        entt::registry& registry,
                        const entt::entity entity)
{
  const auto& spawnpoints = level.spawnpoints();
  if (const auto it = spawnpoints.find(entt::to_integral(entity));
      it != spawnpoints.end()) {
    const auto& data = it->second;
    assert(data.has_type());
    assert(data.has_position());

    auto& spawnpoint = registry.emplace<comp::Spawnpoint>(entity);
    spawnpoint.type = static_cast<comp::SpawnpointType>(data.type());
    spawnpoint.position = restore(data.position());
  }
}

void restore_hitbox(const proto::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& hitboxes = level.hitboxes();
  if (const auto it = hitboxes.find(entt::to_integral(entity)); it != hitboxes.end()) {
    const auto& data = it->second;
    assert(data.has_origin());
    assert(data.has_bounds());
    assert(data.has_enabled());

    auto& hitbox = registry.emplace<comp::Hitbox>(entity);
    hitbox.origin = restore(data.origin());
    hitbox.bounds = restore(data.bounds());
    hitbox.enabled = data.enabled();

    for (const auto& boxData : data.boxes()) {
      assert(boxData.has_offset());
      assert(boxData.has_size());

      auto& box = hitbox.boxes.emplace_back();
      box.offset = restore(boxData.offset());
      box.size = restore(boxData.size());
    }
  }
}

void restore_object(const proto::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& objects = level.objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;
    assert(data.has_id());

    auto& object = registry.emplace<comp::Object>(entity);
    object.id = data.id();
  }
}

void restore_portal(const proto::level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& portals = level.portals();
  if (const auto it = portals.find(entt::to_integral(entity)); it != portals.end()) {
    const auto& data = it->second;
    assert(data.has_path());

    auto& portal = registry.emplace<comp::Portal>(entity);
    portal.path = data.path();
    if (data.has_map_id()) {
      portal.target = map_id{data.map_id()};
    }
  }
}

void restore_tile_layer(const proto::level& level,
                        entt::registry& registry,
                        const entt::entity entity)
{
  const auto& layers = level.tile_layers();
  if (const auto it = layers.find(entt::to_integral(entity)); it != layers.end()) {
    const auto& data = it->second;
    assert(data.has_z_index());
    assert(data.has_matrix());

    auto& layer = registry.emplace<comp::TileLayer>(entity);
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

void restore_tileset(const proto::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& tilesets = level.tilesets();
  if (const auto it = tilesets.find(entt::to_integral(entity)); it != tilesets.end()) {
    const auto& data = it->second;

    auto& tileset = registry.emplace<comp::Tileset>(entity);
    for (const auto& [id, tileEntity] : data.tile_to_entity()) {
      tileset.tiles.try_emplace(tile_id{id}, entt::entity{tileEntity});
    }
  }
}

void restore_inventory(const proto::level& level,
                       entt::registry& registry,
                       const entt::entity entity)
{
  const auto& inventories = level.inventories();
  if (const auto it = inventories.find(entt::to_integral(entity));
      it != inventories.end()) {
    const auto& data = it->second;
    assert(data.has_capacity());

    auto& inventory = registry.emplace<comp::Inventory>(entity);
    inventory.capacity = data.capacity();

    for (const auto itemEntity : data.items()) {
      inventory.items.emplace_back(entt::entity{itemEntity});
    }
  }
}

void restore_tile_object(const proto::level& level,
                         entt::registry& registry,
                         const entt::entity entity)
{
  const auto& objects = level.tile_objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;
    assert(data.has_tile_entity());

    auto& object = registry.emplace<comp::TileObject>(entity);
    object.tile_entity = entt::entity{data.tile_entity()};
  }
}

void restore_trigger(const proto::level& level,
                     entt::registry& registry,
                     const entt::entity entity)
{
  const auto& triggers = level.triggers();
  if (const auto it = triggers.find(entt::to_integral(entity)); it != triggers.end()) {
    const auto& data = it->second;
    assert(data.has_type());

    auto& trigger = registry.emplace<comp::Trigger>(entity);
    trigger.type = static_cast<comp::TriggerType>(data.type());
  }
}

void restore_association(const proto::level& level,
                         entt::registry& registry,
                         const entt::entity entity)
{
  const auto& associations = level.associations();
  if (const auto it = associations.find(entt::to_integral(entity));
      it != associations.end())
  {
    const auto& data = it->second;
    assert(data.has_entity());

    auto& association = registry.emplace<comp::AssociatedEntity>(entity);
    association.entity = entt::entity{data.entity()};
  }
}

}  // namespace wanderer
