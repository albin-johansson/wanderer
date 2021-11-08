#include "restore_data.hpp"

#include <save.pb.h>

#include <cassert>  // assert

#include <rune/rune.hpp>

#include "components/animation.hpp"
#include "components/associated_entity.hpp"
#include "components/chase.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/inventory.hpp"
#include "components/movable.hpp"
#include "components/object.hpp"
#include "components/particle.hpp"
#include "components/plant.hpp"
#include "components/point_light.hpp"
#include "components/portal.hpp"
#include "components/spawnpoint.hpp"
#include "components/tile.hpp"
#include "components/tile_animation.hpp"
#include "components/tile_layer.hpp"
#include "components/tile_object.hpp"
#include "components/tilemap.hpp"
#include "components/tileset.hpp"
#include "components/trigger.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

auto Restore(const proto::float2& data) -> Vec2
{
  assert(data.has_x());
  assert(data.has_y());

  Vec2 result;
  result.x = data.x();
  result.y = data.y();
  return result;
}

auto Restore(const proto::float3& data) -> Vector3
{
  assert(data.has_x());
  assert(data.has_y());
  assert(data.has_z());

  Vector3 result;
  result.x = data.x();
  result.y = data.y();
  result.z = data.z();
  return result;
}

auto Restore(const proto::irect& data) -> cen::irect
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

auto Restore(const proto::frect& data) -> cen::frect
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

auto Restore(const proto::Color& data) -> cen::color
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

auto Restore(const proto::TimeOfDay& data) -> ctx::TimeOfDay
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
  time.tint = Restore(data.tint());

  return time;
}

void RestoreMovable(const proto::Level& level,
                    entt::registry& registry,
                    const entt::entity entity)
{
  const auto& movables = level.movables();
  if (const auto it = movables.find(entt::to_integral(entity)); it != movables.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_velocity());
    assert(data.has_speed());

    auto& movable = registry.emplace<Movable>(entity);
    movable.position = Restore(data.position());
    movable.velocity = Restore(data.velocity());
    movable.speed = data.speed();
  }
}

void RestoreDrawable(const proto::Level& level,
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

    auto& drawable = registry.emplace<Drawable>(entity);
    drawable.texture = data.texture_index();
    drawable.layer = data.layer_index();
    drawable.depth = data.depth_index();
    drawable.src = Restore(data.src());
    drawable.dst = Restore(data.dst());
  }
}

void RestoreAnimation(const proto::Level& level,
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

    auto& animation = registry.emplace<Animation>(entity);
    animation.frame = data.frame();
    animation.frame_count = data.frame_count();
    animation.delay = ms_t{data.delay()};
    animation.then = ms_t{data.then()};
  }
}

void RestorePlant(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity)
{
  const auto& plants = level.plants();
  if (const auto it = plants.find(entt::to_integral(entity)); it != plants.end()) {
    const auto& data = it->second;
    assert(data.has_current_growth());
    assert(data.has_rate());
    assert(data.has_base_y());
    assert(data.has_tile_height());
    assert(data.has_index());

    auto& plant = registry.emplace<Plant>(entity);
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

void RestoreTile(const proto::Level& level, entt::registry& registry, entt::entity entity)
{
  const auto& tiles = level.tiles();
  if (const auto it = tiles.find(entt::to_integral(entity)); it != tiles.end()) {
    const auto& data = it->second;
    assert(data.has_id());
    assert(data.has_texture_index());
    assert(data.has_depth_index());
    assert(data.has_src());

    auto& tile = registry.emplace<Tile>(entity);
    tile.id = data.id();
    tile.texture = data.texture_index();
    tile.depth = data.depth_index();
    tile.src = Restore(data.src());
  }
}

void RestoreTileAnimations(const proto::Level& level,
                           entt::registry& registry,
                           entt::entity entity)
{
  const auto& animations = level.tile_animations();
  if (const auto it = animations.find(entt::to_integral(entity)); it != animations.end())
  {
    const auto& data = it->second;
    assert(data.has_index());
    assert(data.has_then());

    auto& animation = registry.emplace<TileAnimation>(entity);
    animation.index = data.index();
    animation.then = ms_t{data.then()};

    for (const auto& frameData : data.frames()) {
      assert(frameData.has_tile_id());
      assert(frameData.has_duration());

      auto& frame = animation.frames.emplace_back();
      frame.tile = frameData.tile_id();
      frame.duration = ms_t{frameData.duration()};
    }
  }
}

void RestoreChase(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity)
{
  const auto& chases = level.chases();
  if (const auto it = chases.find(entt::to_integral(entity)); it != chases.end()) {
    const auto& data = it->second;
    assert(data.has_target_entity());
    assert(data.has_range());
    assert(data.has_is_active());

    const auto targetEntity = entt::entity{data.target_entity()};
    assert(registry.valid(targetEntity));

    auto& chase = registry.emplace<Chase>(entity);
    chase.target = targetEntity;
    chase.range = data.range();
    chase.active = data.is_active();
  }
}

void RestoreParticle(const proto::Level& level,
                     entt::registry& registry,
                     entt::entity entity)
{
  const auto& particles = level.particles();
  if (const auto it = particles.find(entt::to_integral(entity)); it != particles.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_acceleration());
    assert(data.has_now());
    assert(data.has_duration());
    assert(data.has_color());

    auto& particle = registry.emplace<Particle>(entity);
    particle.position = Restore(data.position());
    particle.acceleration = Restore(data.acceleration());
    particle.now = data.now();
    particle.duration = data.duration();
    particle.color = Restore(data.color());
  }
}

void RestoreLight(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity)
{
  const auto& lights = level.lights();
  if (const auto it = lights.find(entt::to_integral(entity)); it != lights.end()) {
    const auto& data = it->second;
    assert(data.has_position());
    assert(data.has_size());
    assert(data.has_fluctuation());
    assert(data.has_fluctuation_step());
    assert(data.has_fluctuation_limit());

    auto& light = registry.emplace<PointLight>(entity);
    light.position = Restore(data.position());
    light.size = data.size();
    light.fluctuation = data.fluctuation();
    light.fluctuation_step = data.fluctuation_step();
    light.fluctuation_limit = data.fluctuation_limit();
  }
}

void RestoreSpawnpoint(const proto::Level& level,
                       entt::registry& registry,
                       entt::entity entity)
{
  const auto& spawnpoints = level.spawnpoints();
  if (const auto it = spawnpoints.find(entt::to_integral(entity));
      it != spawnpoints.end()) {
    const auto& data = it->second;
    assert(data.has_type());
    assert(data.has_position());

    auto& spawnpoint = registry.emplace<Spawnpoint>(entity);
    spawnpoint.type = static_cast<SpawnpointType>(data.type());
    spawnpoint.position = Restore(data.position());
  }
}

void RestoreHitbox(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity)
{
  // TODO investigate restored hitboxes, e.g. cauldron

  const auto& hitboxes = level.hitboxes();
  if (const auto it = hitboxes.find(entt::to_integral(entity)); it != hitboxes.end()) {
    const auto& data = it->second;
    assert(data.has_origin());
    assert(data.has_bounds());
    assert(data.has_enabled());

    auto& hitbox = registry.emplace<Hitbox>(entity);
    hitbox.origin = Restore(data.origin());
    hitbox.bounds = Restore(data.bounds());
    hitbox.enabled = data.enabled();

    for (const auto& boxData : data.boxes()) {
      assert(boxData.has_offset());
      assert(boxData.has_size());

      auto& box = hitbox.boxes.emplace_back();
      box.offset = Restore(boxData.offset());
      box.size.width = boxData.size().x();
      box.size.height = boxData.size().y();
    }
  }
}

void RestoreObject(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity)
{
  const auto& objects = level.objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;
    assert(data.has_id());

    auto& object = registry.emplace<Object>(entity);
    object.id = data.id();
  }
}

void RestorePortal(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity)
{
  const auto& portals = level.portals();
  if (const auto it = portals.find(entt::to_integral(entity)); it != portals.end()) {
    const auto& data = it->second;
    assert(data.has_path());

    auto& portal = registry.emplace<Portal>(entity);
    portal.path = data.path();
    if (data.has_map_id()) {
      portal.target = data.map_id();
    }
  }
}

void RestoreTileLayer(const proto::Level& level,
                      entt::registry& registry,
                      entt::entity entity)
{
  const auto& layers = level.tile_layers();
  if (const auto it = layers.find(entt::to_integral(entity)); it != layers.end()) {
    const auto& data = it->second;
    assert(data.has_z_index());
    assert(data.has_matrix());

    auto& layer = registry.emplace<TileLayer>(entity);
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

void RestoreTileset(const proto::Level& level,
                    entt::registry& registry,
                    entt::entity entity)
{
  const auto& tilesets = level.tilesets();
  if (const auto it = tilesets.find(entt::to_integral(entity)); it != tilesets.end()) {
    const auto& data = it->second;

    auto& tileset = registry.emplace<Tileset>(entity);
    for (const auto& [id, tileEntity] : data.tile_to_entity()) {
      tileset.tiles.try_emplace(id, entt::entity{tileEntity});
    }
  }
}

void RestoreInventory(const proto::Level& level,
                      entt::registry& registry,
                      entt::entity entity)
{
  const auto& inventories = level.inventories();
  if (const auto it = inventories.find(entt::to_integral(entity));
      it != inventories.end()) {
    const auto& data = it->second;
    assert(data.has_capacity());

    auto& inventory = registry.emplace<Inventory>(entity);
    inventory.capacity = data.capacity();

    for (const auto itemEntity : data.items()) {
      inventory.items.emplace_back(entt::entity{itemEntity});
    }
  }
}

void RestoreTileObject(const proto::Level& level,
                       entt::registry& registry,
                       entt::entity entity)
{
  const auto& objects = level.tile_objects();
  if (const auto it = objects.find(entt::to_integral(entity)); it != objects.end()) {
    const auto& data = it->second;
    assert(data.has_tile_entity());

    auto& object = registry.emplace<TileObject>(entity);
    object.tile_entity = entt::entity{data.tile_entity()};
  }
}

void RestoreTrigger(const proto::Level& level,
                    entt::registry& registry,
                    entt::entity entity)
{
  const auto& triggers = level.triggers();
  if (const auto it = triggers.find(entt::to_integral(entity)); it != triggers.end()) {
    const auto& data = it->second;
    assert(data.has_type());

    auto& trigger = registry.emplace<Trigger>(entity);
    trigger.type = static_cast<TriggerType>(data.type());
  }
}

void RestoreAssociation(const proto::Level& level,
                        entt::registry& registry,
                        entt::entity entity)
{
  const auto& associations = level.associations();
  if (const auto it = associations.find(entt::to_integral(entity));
      it != associations.end())
  {
    const auto& data = it->second;
    assert(data.has_entity());

    auto& association = registry.emplace<AssociatedEntity>(entity);
    association.entity = entt::entity{data.entity()};
  }
}

}  // namespace wanderer
