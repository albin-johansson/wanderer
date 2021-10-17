#include "save_shared_registry.hpp"

#include <save.pb.h>

#include <cassert>  // assert
#include <fstream>  // ofstream
#include <ios>      // ios

#include "common/float2.hpp"
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

namespace wanderer {
namespace {

void copy_to(const float2& src, proto::float2* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
}

void copy_to(const comp::Vector3& src, proto::float3* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
  dst->set_z(src.z);
}

void copy_to(const cen::irect& src, proto::irect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void copy_to(const cen::frect& src, proto::frect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void copy_to(const cen::farea& src, proto::farea* dst)
{
  dst->set_width(src.width);
  dst->set_height(src.height);
}

void copy_to(const cen::color& src, proto::color* dst)
{
  dst->set_red(src.red());
  dst->set_green(src.green());
  dst->set_blue(src.blue());
  dst->set_alpha(src.alpha());
}

void copy_to(const ctx::TimeOfDay& src, proto::time_of_day* dst)
{
  dst->set_hour(src.hour);
  dst->set_minute(src.minute);
  dst->set_seconds(src.seconds);
  dst->set_week(src.week);
  dst->set_day(static_cast<proto::day_of_week>(src.day));
  copy_to(src.tint, dst->mutable_tint());
}

void copy_to(const comp::Movable& src, proto::movable& dst)
{
  copy_to(src.position, dst.mutable_position());
  copy_to(src.velocity, dst.mutable_velocity());
  dst.set_speed(src.speed);
}

void copy_to(const comp::Drawable& src, proto::drawable& dst)
{
  copy_to(src.src, dst.mutable_src());
  copy_to(src.dst, dst.mutable_dst());
  dst.set_texture_index(src.texture);
  dst.set_layer_index(src.layer);
  dst.set_depth_index(src.depth);
}

void copy_to(const comp::Animation& src, proto::animation& dst)
{
  dst.set_frame(src.frame);
  dst.set_frame_count(src.frame_count);
  dst.set_then(src.then.count());
  dst.set_delay(src.delay.count());
}

void copy_to(const comp::Plant& src, proto::plant& dst)
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

void copy_to(const comp::Tile& src, proto::tile& dst)
{
  copy_to(src.src, dst.mutable_src());
  dst.set_id(src.id);
  dst.set_texture_index(src.texture);
  dst.set_depth_index(src.depth);
}

void copy_to(const comp::Tilemap& src, proto::tilemap& dst)
{
  copy_to(src.size, dst.mutable_size());
  dst.set_id(src.id);
  dst.set_humanoid_layer_index(src.humanoid_layer);
  dst.set_row_count(src.row_count);
  dst.set_column_count(src.col_count);
}

void copy_to(const comp::TileAnimation& src, proto::tile_animation& dst)
{
  dst.set_index(src.index);
  dst.set_then(src.then.count());

  for (const auto& frame : src.frames) {
    auto* frameData = dst.add_frames();
    frameData->set_tile_id(frame.tile);
    frameData->set_duration(frame.duration.count());
  }
}

void copy_to(const comp::Chase& src, proto::chase& dst)
{
  dst.set_target_entity(entt::to_integral(src.target));
  dst.set_range(src.range);
  dst.set_is_active(src.active);
}

void copy_to(const comp::particle& src, proto::particle& dst)
{
  copy_to(src.position, dst.mutable_position());
  copy_to(src.acceleration, dst.mutable_acceleration());
  copy_to(src.color, dst.mutable_color());
  dst.set_now(src.now);
  dst.set_duration(src.duration);
}

void copy_to(const comp::PointLight& src, proto::point_light& dst)
{
  copy_to(src.position, dst.mutable_position());
  dst.set_size(src.size);
  dst.set_fluctuation(src.fluctuation);
  dst.set_fluctuation_step(src.fluctuation_step);
  dst.set_fluctuation_limit(src.fluctuation_limit);
}

void copy_to(const comp::Spawnpoint& src, proto::spawnpoint& dst)
{
  copy_to(src.position, dst.mutable_position());
  dst.set_type(static_cast<proto::spawnpoint_type>(src.type));
}

void copy_to(const comp::Hitbox& src, proto::hitbox& dst)
{
  copy_to(src.origin, dst.mutable_origin());
  copy_to(src.bounds, dst.mutable_bounds());
  dst.set_enabled(src.enabled);

  for (const auto& box : src.boxes) {
    auto* boxData = dst.add_boxes();
    copy_to(box.offset, boxData->mutable_offset());
    copy_to(box.size, boxData->mutable_size());
  }
}

void copy_to(const comp::Object& src, proto::map_object& dst)
{
  dst.set_id(src.id);
}

void copy_to(const comp::Portal& src, proto::portal& dst)
{
  if (src.target) {
    dst.set_map_id(*src.target);
  }
  dst.set_path(src.path);
}

void copy_to(const comp::TileLayer& src, proto::tile_layer& dst)
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

void copy_to(const comp::Tileset& src, proto::tileset& dst)
{
  auto& map = *dst.mutable_tile_to_entity();
  for (const auto& [id, entity] : src.tiles) {
    map[id] = entt::to_integral(entity);
  }
}

void copy_to(const comp::Inventory& src, proto::inventory& dst)
{
  dst.set_capacity(src.capacity);
  for (const auto entity : src.items) {
    dst.add_items(entt::to_integral(entity));
  }
}

void copy_to(const comp::TileObject& src, proto::tile_object& dst)
{
  dst.set_tile_entity(entt::to_integral(src.tile_entity));
}

void copy_to(const comp::Trigger& src, proto::trigger& dst)
{
  dst.set_type(static_cast<proto::trigger_type>(src.type));
}

void copy_to(const comp::AssociatedEntity& src, proto::associated_entity& dst)
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
      copy_to(*movable, (*data->mutable_movables())[value]);
    }

    if (const auto* drawable = registry.try_get<comp::Drawable>(entity)) {
      copy_to(*drawable, (*data->mutable_drawables())[value]);
    }

    if (const auto* animation = registry.try_get<comp::Animation>(entity)) {
      copy_to(*animation, (*data->mutable_animations())[value]);
    }

    if (const auto* plant = registry.try_get<comp::Plant>(entity)) {
      copy_to(*plant, (*data->mutable_plants())[value]);
    }

    if (const auto* tile = registry.try_get<comp::Tile>(entity)) {
      copy_to(*tile, (*data->mutable_tiles())[value]);
    }

    if (const auto* tilemap = registry.try_get<comp::Tilemap>(entity)) {
      copy_to(*tilemap, (*data->mutable_tilemaps())[value]);
    }

    if (const auto* animation = registry.try_get<comp::TileAnimation>(entity)) {
      copy_to(*animation, (*data->mutable_tile_animations())[value]);
    }

    if (const auto* chase = registry.try_get<comp::Chase>(entity)) {
      copy_to(*chase, (*data->mutable_chases())[value]);
    }

    if (const auto* particle = registry.try_get<comp::particle>(entity)) {
      copy_to(*particle, (*data->mutable_particles())[value]);
    }

    if (const auto* light = registry.try_get<comp::PointLight>(entity)) {
      copy_to(*light, (*data->mutable_lights())[value]);
    }

    if (const auto* spawnpoint = registry.try_get<comp::Spawnpoint>(entity)) {
      copy_to(*spawnpoint, (*data->mutable_spawnpoints())[value]);
    }

    if (const auto* hitbox = registry.try_get<comp::Hitbox>(entity)) {
      copy_to(*hitbox, (*data->mutable_hitboxes())[value]);
    }

    if (const auto* object = registry.try_get<comp::Object>(entity)) {
      copy_to(*object, (*data->mutable_objects())[value]);
    }

    if (const auto* portal = registry.try_get<comp::Portal>(entity)) {
      copy_to(*portal, (*data->mutable_portals())[value]);
    }

    if (const auto* layer = registry.try_get<comp::TileLayer>(entity)) {
      copy_to(*layer, (*data->mutable_tile_layers())[value]);
    }

    if (const auto* tileset = registry.try_get<comp::Tileset>(entity)) {
      copy_to(*tileset, (*data->mutable_tilesets())[value]);
    }

    if (const auto* inventory = registry.try_get<comp::Inventory>(entity)) {
      copy_to(*inventory, (*data->mutable_inventories())[value]);
    }

    if (const auto* object = registry.try_get<comp::TileObject>(entity)) {
      copy_to(*object, (*data->mutable_tile_objects())[value]);
    }

    if (const auto* trigger = registry.try_get<comp::Trigger>(entity)) {
      copy_to(*trigger, (*data->mutable_triggers())[value]);
    }

    if (const auto* association = registry.try_get<comp::AssociatedEntity>(entity)) {
      copy_to(*association, (*data->mutable_associations())[value]);
    }
  });

  const auto& viewport = registry.ctx<ctx::Viewport>();
  data->set_is_outside_level(viewport.keep_in_bounds);
}

void save_shared_data(const entt::registry& shared, proto::shared_data* data)
{
  copy_to(shared.ctx<ctx::TimeOfDay>(), data->mutable_time());
}

void save_data(const entt::registry& shared, proto::save& save)
{
  save.set_current_level_id(sys::CurrentLevel(shared).id);
  save_shared_data(shared, save.mutable_shared());

  for (auto&& [entity, level] : shared.view<comp::Level>().each()) {
    auto* data = save.add_levels();
    data->set_id(level.id);
    data->set_is_outside_level(shared.all_of<comp::OutsideLevel>(entity));
    save_level(level.registry, data);
  }
}

}  // namespace

void save_shared_registry(const entt::registry& shared, const std::filesystem::path& path)
{
  std::ofstream stream{path, std::ios::out | std::ios::trunc | std::ios::binary};

  proto::save save;
  save_data(shared, save);

  if (!save.SerializeToOstream(&stream)) {
    CENTURION_LOG_ERROR("Something went wrong when trying to create a save file!");
  }
}

}  // namespace wanderer
