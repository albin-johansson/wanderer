#include "save_shared_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert
#include <fstream>  // ofstream
#include <ios>      // ios

#include "components/animation.hpp"
#include "components/associated_entity.hpp"
#include "components/chase.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/humanoid.hpp"
#include "components/inventory.hpp"
#include "components/level.hpp"
#include "components/movable.hpp"
#include "components/object.hpp"
#include "components/particle.hpp"
#include "components/plant.hpp"
#include "components/player.hpp"
#include "components/point_light.hpp"
#include "components/portal.hpp"
#include "components/spawnpoint.hpp"
#include "components/tile.hpp"
#include "components/tile_animation.hpp"
#include "components/tile_layer.hpp"
#include "components/tile_object.hpp"
#include "components/tilemap.hpp"
#include "components/tileset.hpp"
#include "components/time_of_day.hpp"
#include "components/trigger.hpp"
#include "components/vector3.hpp"
#include "components/viewport.hpp"
#include "systems/level_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace {

void CopyTo(const Vec2& src, proto::float2* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
}

void CopyTo(const cen::farea& src, proto::float2* dst)
{
  dst->set_x(src.width);
  dst->set_y(src.height);
}

void CopyTo(const Vector3& src, proto::float3* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
  dst->set_z(src.z);
}

void CopyTo(const cen::irect& src, proto::irect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void CopyTo(const cen::frect& src, proto::frect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void CopyTo(const cen::color& src, proto::Color* dst)
{
  dst->set_red(src.red());
  dst->set_green(src.green());
  dst->set_blue(src.blue());
  dst->set_alpha(src.alpha());
}

void CopyTo(const ctx::TimeOfDay& src, proto::TimeOfDay* dst)
{
  dst->set_hour(src.hour);
  dst->set_minute(src.minute);
  dst->set_seconds(src.seconds);
  dst->set_week(src.week);
  dst->set_day(static_cast<proto::DayOfWeek>(src.day));
  CopyTo(src.tint, dst->mutable_tint());
}

void CopyTo(const Movable& src, proto::Movable& dst)
{
  CopyTo(src.position, dst.mutable_position());
  CopyTo(src.velocity, dst.mutable_velocity());
  dst.set_speed(src.speed);
}

void CopyTo(const Drawable& src, proto::Drawable& dst)
{
  CopyTo(src.src, dst.mutable_src());
  CopyTo(src.dst, dst.mutable_dst());
  dst.set_texture_index(src.texture);
  dst.set_layer_index(src.layer);
  dst.set_depth_index(src.depth);
}

void CopyTo(const Animation& src, proto::Animation& dst)
{
  dst.set_frame(src.frame);
  dst.set_frame_count(src.frame_count);
  dst.set_then(src.then.count());
  dst.set_delay(src.delay.count());
}

void CopyTo(const Plant& src, proto::Plant& dst)
{
  dst.set_current_growth(src.current);
  dst.set_rate(src.rate);

  dst.set_base_y(src.base_y);
  dst.set_tile_height(src.tile_height);

  dst.set_index(src.index);

  for (const auto id : src.tiles) {
    dst.add_tiles(id);
  }

  for (const auto id : src.tall) {
    dst.add_tall_tiles(id);
  }
}

void CopyTo(const Tile& src, proto::Tile& dst)
{
  CopyTo(src.src, dst.mutable_src());
  dst.set_id(src.id);
  dst.set_texture_index(src.texture);
  dst.set_depth_index(src.depth);
}

void CopyTo(const TileAnimation& src, proto::TileAnimation& dst)
{
  dst.set_index(src.index);
  dst.set_then(src.then.count());

  for (const auto& frame : src.frames) {
    auto* frameData = dst.add_frames();
    frameData->set_tile_id(frame.tile);
    frameData->set_duration(frame.duration.count());
  }
}

void CopyTo(const Chase& src, proto::Chase& dst)
{
  dst.set_target_entity(entt::to_integral(src.target));
  dst.set_range(src.range);
  dst.set_is_active(src.active);
}

void CopyTo(const Particle& src, proto::Particle& dst)
{
  CopyTo(src.position, dst.mutable_position());
  CopyTo(src.acceleration, dst.mutable_acceleration());
  CopyTo(src.color, dst.mutable_color());
  dst.set_now(src.now);
  dst.set_duration(src.duration);
}

void CopyTo(const PointLight& src, proto::PointLight& dst)
{
  CopyTo(src.position, dst.mutable_position());
  dst.set_size(src.size);
  dst.set_fluctuation(src.fluctuation);
  dst.set_fluctuation_step(src.fluctuation_step);
  dst.set_fluctuation_limit(src.fluctuation_limit);
}

void CopyTo(const Spawnpoint& src, proto::Spawnpoint& dst)
{
  CopyTo(src.position, dst.mutable_position());
  dst.set_type(static_cast<proto::SpawnpointType>(src.type));
}

void CopyTo(const Hitbox& src, proto::Hitbox& dst)
{
  CopyTo(src.origin, dst.mutable_origin());
  CopyTo(src.bounds, dst.mutable_bounds());
  dst.set_enabled(src.enabled);

  for (const auto& box : src.boxes) {
    auto* boxData = dst.add_boxes();
    CopyTo(box.offset, boxData->mutable_offset());
    CopyTo(box.size, boxData->mutable_size());
  }
}

void CopyTo(const Object& src, proto::MapObject& dst)
{
  dst.set_id(src.id);
}

void CopyTo(const Portal& src, proto::Portal& dst)
{
  if (src.target) {
    dst.set_map_id(*src.target);
  }
  dst.set_path(src.path.string());
}

void CopyTo(const TileLayer& src, proto::TileLayer& dst)
{
  dst.set_z_index(src.z);

  auto* matrix = dst.mutable_matrix();
  for (const auto& row : src.matrix) {
    auto* rowData = matrix->add_rows();
    for (const auto tile : row) {
      rowData->add_tiles(tile);
    }
  }
}

void CopyTo(const Tileset& src, proto::Tileset& dst)
{
  auto& map = *dst.mutable_tile_to_entity();
  for (const auto& [id, entity] : src.tiles) {
    map[id] = entt::to_integral(entity);
  }
}

void CopyTo(const Inventory& src, proto::Inventory& dst)
{
  dst.set_capacity(src.capacity);
  for (const auto entity : src.items) {
    dst.add_items(entt::to_integral(entity));
  }
}

void CopyTo(const TileObject& src, proto::TileObject& dst)
{
  dst.set_tile_entity(entt::to_integral(src.tile_entity));
}

void CopyTo(const Trigger& src, proto::Trigger& dst)
{
  dst.set_type(static_cast<proto::TriggerType>(src.type));
}

void CopyTo(const AssociatedEntity& src, proto::AssociatedEntity& dst)
{
  dst.set_entity(entt::to_integral(src.entity));
}

void SaveLevel(const entt::registry& registry, proto::Level* data)  // NOLINT complexity
{
  const auto& tilemap = registry.ctx<Tilemap>();
  data->set_humanoid_layer_index(tilemap.humanoid_layer);
  data->set_row_count(tilemap.row_count);
  data->set_column_count(tilemap.col_count);

  registry.each([&](const entt::entity entity) {
    const auto value = entt::to_integral(entity);
    data->add_entities(value);

    if (registry.all_of<Player>(entity)) {
      assert(!data->has_player_entity());
      data->set_player_entity(value);
    }

    if (registry.all_of<Humanoid>(entity)) {
      data->add_humanoids(value);
    }

    if (const auto* movable = registry.try_get<Movable>(entity)) {
      CopyTo(*movable, (*data->mutable_movables())[value]);
    }

    if (const auto* drawable = registry.try_get<Drawable>(entity)) {
      CopyTo(*drawable, (*data->mutable_drawables())[value]);
    }

    if (const auto* animation = registry.try_get<Animation>(entity)) {
      CopyTo(*animation, (*data->mutable_animations())[value]);
    }

    if (const auto* plant = registry.try_get<Plant>(entity)) {
      CopyTo(*plant, (*data->mutable_plants())[value]);
    }

    if (const auto* tile = registry.try_get<Tile>(entity)) {
      CopyTo(*tile, (*data->mutable_tiles())[value]);
    }

    if (const auto* animation = registry.try_get<TileAnimation>(entity)) {
      CopyTo(*animation, (*data->mutable_tile_animations())[value]);
    }

    if (const auto* chase = registry.try_get<Chase>(entity)) {
      CopyTo(*chase, (*data->mutable_chases())[value]);
    }

    if (const auto* particle = registry.try_get<Particle>(entity)) {
      CopyTo(*particle, (*data->mutable_particles())[value]);
    }

    if (const auto* light = registry.try_get<PointLight>(entity)) {
      CopyTo(*light, (*data->mutable_lights())[value]);
    }

    if (const auto* spawnpoint = registry.try_get<Spawnpoint>(entity)) {
      CopyTo(*spawnpoint, (*data->mutable_spawnpoints())[value]);
    }

    if (const auto* hitbox = registry.try_get<Hitbox>(entity)) {
      CopyTo(*hitbox, (*data->mutable_hitboxes())[value]);
    }

    if (const auto* object = registry.try_get<Object>(entity)) {
      CopyTo(*object, (*data->mutable_objects())[value]);
    }

    if (const auto* portal = registry.try_get<Portal>(entity)) {
      CopyTo(*portal, (*data->mutable_portals())[value]);
    }

    if (const auto* layer = registry.try_get<TileLayer>(entity)) {
      CopyTo(*layer, (*data->mutable_tile_layers())[value]);
    }

    if (const auto* tileset = registry.try_get<Tileset>(entity)) {
      CopyTo(*tileset, (*data->mutable_tilesets())[value]);
    }

    if (const auto* inventory = registry.try_get<Inventory>(entity)) {
      CopyTo(*inventory, (*data->mutable_inventories())[value]);
    }

    if (const auto* object = registry.try_get<TileObject>(entity)) {
      CopyTo(*object, (*data->mutable_tile_objects())[value]);
    }

    if (const auto* trigger = registry.try_get<Trigger>(entity)) {
      CopyTo(*trigger, (*data->mutable_triggers())[value]);
    }

    if (const auto* association = registry.try_get<AssociatedEntity>(entity)) {
      CopyTo(*association, (*data->mutable_associations())[value]);
    }
  });

  const auto& viewport = registry.ctx<ctx::Viewport>();
  data->set_is_outside_level(viewport.keep_in_bounds);
}

void SaveSharedData(const entt::registry& shared, proto::SharedData* data)
{
  CopyTo(shared.ctx<ctx::TimeOfDay>(), data->mutable_time());
}

void SaveData(const entt::registry& shared, proto::Save& save)
{
  save.set_current_level_id(sys::CurrentLevel(shared).id);
  SaveSharedData(shared, save.mutable_shared());

  for (auto&& [entity, level] : shared.view<Level>().each()) {
    auto* data = save.add_levels();
    data->set_id(level.id);
    data->set_is_outside_level(shared.all_of<OutsideLevel>(entity));
    SaveLevel(level.registry, data);
  }
}

}  // namespace

void SaveSharedRegistry(const entt::registry& shared, const std::filesystem::path& path)
{
  std::ofstream stream{path, std::ios::out | std::ios::trunc | std::ios::binary};

  proto::Save save;
  SaveData(shared, save);

  if (!save.SerializeToOstream(&stream)) {
    CENTURION_LOG_ERROR("Something went wrong when trying to create a save file!");
  }
}

}  // namespace wanderer
