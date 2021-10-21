#include "save_shared_registry.hpp"

#include <cassert>  // assert
#include <fstream>  // ofstream
#include <ios>      // ios

#include <save.pb.h>

#include "components/ai/chase.hpp"
#include "components/ai/humanoid.hpp"
#include "components/associated_entity.hpp"
#include "components/ctx/time_of_day.hpp"
#include "components/ctx/viewport.hpp"
#include "components/gfx/animation.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/level.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/physics/hitbox.hpp"
#include "components/physics/movable.hpp"
#include "components/physics/particle.hpp"
#include "components/physics/vector3.hpp"
#include "components/plant.hpp"
#include "components/player.hpp"
#include "components/tiles/tile.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "components/trigger.hpp"
#include "systems/levels/level_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace {

void CopyTo(const float2& src, proto::float2* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
}

void CopyTo(const comp::Vector3& src, proto::float3* dst)
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

void CopyTo(const cen::farea& src, proto::farea* dst)
{
  dst->set_width(src.width);
  dst->set_height(src.height);
}

void CopyTo(const cen::color& src, proto::color* dst)
{
  dst->set_red(src.red());
  dst->set_green(src.green());
  dst->set_blue(src.blue());
  dst->set_alpha(src.alpha());
}

void CopyTo(const ctx::TimeOfDay& src, proto::time_of_day* dst)
{
  dst->set_hour(src.hour);
  dst->set_minute(src.minute);
  dst->set_seconds(src.seconds);
  dst->set_week(src.week);
  dst->set_day(static_cast<proto::day_of_week>(src.day));
  CopyTo(src.tint, dst->mutable_tint());
}

void CopyTo(const comp::Movable& src, proto::movable& dst)
{
  CopyTo(src.position, dst.mutable_position());
  CopyTo(src.velocity, dst.mutable_velocity());
  dst.set_speed(src.speed);
}

void CopyTo(const comp::Drawable& src, proto::drawable& dst)
{
  CopyTo(src.src, dst.mutable_src());
  CopyTo(src.dst, dst.mutable_dst());
  dst.set_texture_index(src.texture);
  dst.set_layer_index(src.layer);
  dst.set_depth_index(src.depth);
}

void CopyTo(const comp::Animation& src, proto::animation& dst)
{
  dst.set_frame(src.frame);
  dst.set_frame_count(src.frame_count);
  dst.set_then(src.then.count());
  dst.set_delay(src.delay.count());
}

void CopyTo(const comp::Plant& src, proto::plant& dst)
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

void CopyTo(const comp::Tile& src, proto::tile& dst)
{
  CopyTo(src.src, dst.mutable_src());
  dst.set_id(src.id);
  dst.set_texture_index(src.texture);
  dst.set_depth_index(src.depth);
}

void CopyTo(const comp::Tilemap& src, proto::tilemap& dst)
{
  CopyTo(src.size, dst.mutable_size());
  dst.set_id(src.id);
  dst.set_humanoid_layer_index(src.humanoid_layer);
  dst.set_row_count(src.row_count);
  dst.set_column_count(src.col_count);
}

void CopyTo(const comp::TileAnimation& src, proto::tile_animation& dst)
{
  dst.set_index(src.index);
  dst.set_then(src.then.count());

  for (const auto& frame : src.frames) {
    auto* frameData = dst.add_frames();
    frameData->set_tile_id(frame.tile);
    frameData->set_duration(frame.duration.count());
  }
}

void CopyTo(const comp::Chase& src, proto::chase& dst)
{
  dst.set_target_entity(entt::to_integral(src.target));
  dst.set_range(src.range);
  dst.set_is_active(src.active);
}

void CopyTo(const comp::particle& src, proto::particle& dst)
{
  CopyTo(src.position, dst.mutable_position());
  CopyTo(src.acceleration, dst.mutable_acceleration());
  CopyTo(src.color, dst.mutable_color());
  dst.set_now(src.now);
  dst.set_duration(src.duration);
}

void CopyTo(const comp::PointLight& src, proto::point_light& dst)
{
  CopyTo(src.position, dst.mutable_position());
  dst.set_size(src.size);
  dst.set_fluctuation(src.fluctuation);
  dst.set_fluctuation_step(src.fluctuation_step);
  dst.set_fluctuation_limit(src.fluctuation_limit);
}

void CopyTo(const comp::Spawnpoint& src, proto::spawnpoint& dst)
{
  CopyTo(src.position, dst.mutable_position());
  dst.set_type(static_cast<proto::spawnpoint_type>(src.type));
}

void CopyTo(const comp::Hitbox& src, proto::hitbox& dst)
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

void CopyTo(const comp::Object& src, proto::map_object& dst)
{
  dst.set_id(src.id);
}

void CopyTo(const comp::Portal& src, proto::portal& dst)
{
  if (src.target) {
    dst.set_map_id(*src.target);
  }
  dst.set_path(src.path);
}

void CopyTo(const comp::TileLayer& src, proto::tile_layer& dst)
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

void CopyTo(const comp::Tileset& src, proto::tileset& dst)
{
  auto& map = *dst.mutable_tile_to_entity();
  for (const auto& [id, entity] : src.tiles) {
    map[id] = entt::to_integral(entity);
  }
}

void CopyTo(const comp::Inventory& src, proto::inventory& dst)
{
  dst.set_capacity(src.capacity);
  for (const auto entity : src.items) {
    dst.add_items(entt::to_integral(entity));
  }
}

void CopyTo(const comp::TileObject& src, proto::tile_object& dst)
{
  dst.set_tile_entity(entt::to_integral(src.tile_entity));
}

void CopyTo(const comp::Trigger& src, proto::trigger& dst)
{
  dst.set_type(static_cast<proto::trigger_type>(src.type));
}

void CopyTo(const comp::AssociatedEntity& src, proto::associated_entity& dst)
{
  dst.set_entity(entt::to_integral(src.entity));
}

void save_level(const entt::registry& registry, proto::level* data)  // NOLINT
{
  registry.each([&](const entt::entity entity) {
    const auto value = entt::to_integral(entity);
    data->add_entities(value);

    if (registry.all_of<comp::Player>(entity)) {
      assert(!data->has_player_entity());
      data->set_player_entity(value);
    }

    if (registry.all_of<comp::Humanoid>(entity)) {
      data->add_humanoids(value);
    }

    if (const auto* movable = registry.try_get<comp::Movable>(entity)) {
      CopyTo(*movable, (*data->mutable_movables())[value]);
    }

    if (const auto* drawable = registry.try_get<comp::Drawable>(entity)) {
      CopyTo(*drawable, (*data->mutable_drawables())[value]);
    }

    if (const auto* animation = registry.try_get<comp::Animation>(entity)) {
      CopyTo(*animation, (*data->mutable_animations())[value]);
    }

    if (const auto* plant = registry.try_get<comp::Plant>(entity)) {
      CopyTo(*plant, (*data->mutable_plants())[value]);
    }

    if (const auto* tile = registry.try_get<comp::Tile>(entity)) {
      CopyTo(*tile, (*data->mutable_tiles())[value]);
    }

    if (const auto* tilemap = registry.try_get<comp::Tilemap>(entity)) {
      CopyTo(*tilemap, (*data->mutable_tilemaps())[value]);
    }

    if (const auto* animation = registry.try_get<comp::TileAnimation>(entity)) {
      CopyTo(*animation, (*data->mutable_tile_animations())[value]);
    }

    if (const auto* chase = registry.try_get<comp::Chase>(entity)) {
      CopyTo(*chase, (*data->mutable_chases())[value]);
    }

    if (const auto* particle = registry.try_get<comp::particle>(entity)) {
      CopyTo(*particle, (*data->mutable_particles())[value]);
    }

    if (const auto* light = registry.try_get<comp::PointLight>(entity)) {
      CopyTo(*light, (*data->mutable_lights())[value]);
    }

    if (const auto* spawnpoint = registry.try_get<comp::Spawnpoint>(entity)) {
      CopyTo(*spawnpoint, (*data->mutable_spawnpoints())[value]);
    }

    if (const auto* hitbox = registry.try_get<comp::Hitbox>(entity)) {
      CopyTo(*hitbox, (*data->mutable_hitboxes())[value]);
    }

    if (const auto* object = registry.try_get<comp::Object>(entity)) {
      CopyTo(*object, (*data->mutable_objects())[value]);
    }

    if (const auto* portal = registry.try_get<comp::Portal>(entity)) {
      CopyTo(*portal, (*data->mutable_portals())[value]);
    }

    if (const auto* layer = registry.try_get<comp::TileLayer>(entity)) {
      CopyTo(*layer, (*data->mutable_tile_layers())[value]);
    }

    if (const auto* tileset = registry.try_get<comp::Tileset>(entity)) {
      CopyTo(*tileset, (*data->mutable_tilesets())[value]);
    }

    if (const auto* inventory = registry.try_get<comp::Inventory>(entity)) {
      CopyTo(*inventory, (*data->mutable_inventories())[value]);
    }

    if (const auto* object = registry.try_get<comp::TileObject>(entity)) {
      CopyTo(*object, (*data->mutable_tile_objects())[value]);
    }

    if (const auto* trigger = registry.try_get<comp::Trigger>(entity)) {
      CopyTo(*trigger, (*data->mutable_triggers())[value]);
    }

    if (const auto* association = registry.try_get<comp::AssociatedEntity>(entity)) {
      CopyTo(*association, (*data->mutable_associations())[value]);
    }
  });

  const auto& viewport = registry.ctx<ctx::Viewport>();
  data->set_is_outside_level(viewport.keep_in_bounds);
}

void SaveSharedData(const entt::registry& shared, proto::shared_data* data)
{
  CopyTo(shared.ctx<ctx::TimeOfDay>(), data->mutable_time());
}

void SaveData(const entt::registry& shared, proto::save& save)
{
  save.set_current_level_id(sys::CurrentLevel(shared).id);
  SaveSharedData(shared, save.mutable_shared());

  for (auto&& [entity, level] : shared.view<comp::Level>().each()) {
    auto* data = save.add_levels();
    data->set_id(level.id);
    data->set_is_outside_level(shared.all_of<comp::OutsideLevel>(entity));
    save_level(level.registry, data);
  }
}

}  // namespace

void SaveSharedRegistry(const entt::registry& shared, const std::filesystem::path& path)
{
  std::ofstream stream{path, std::ios::out | std::ios::trunc | std::ios::binary};

  proto::save save;
  SaveData(shared, save);

  if (!save.SerializeToOstream(&stream)) {
    CENTURION_LOG_ERROR("Something went wrong when trying to create a save file!");
  }
}

}  // namespace wanderer
