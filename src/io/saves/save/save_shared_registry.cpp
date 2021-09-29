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
#include "components/gfx/animated.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/level.hpp"
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
#include "systems/levels/level_system.hpp"

namespace wanderer {
namespace {

void copy_to(const float2& src, protobuf::float2* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
}

void copy_to(const comp::float3& src, protobuf::float3* dst)
{
  dst->set_x(src.x);
  dst->set_y(src.y);
  dst->set_z(src.z);
}

void copy_to(const cen::irect& src, protobuf::irect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void copy_to(const cen::frect& src, protobuf::frect* dst)
{
  dst->set_x(src.x());
  dst->set_y(src.y());
  dst->set_width(src.width());
  dst->set_height(src.height());
}

void copy_to(const cen::farea& src, protobuf::farea* dst)
{
  dst->set_width(src.width);
  dst->set_height(src.height);
}

void copy_to(const cen::color& src, protobuf::color* dst)
{
  dst->set_red(src.red());
  dst->set_green(src.green());
  dst->set_blue(src.blue());
  dst->set_alpha(src.alpha());
}

void copy_to(const ctx::time_of_day& src, protobuf::time_of_day* dst)
{
  dst->set_hour(src.hour);
  dst->set_minute(src.minute);
  dst->set_seconds(src.seconds);
  dst->set_week(src.week);
  dst->set_day(static_cast<protobuf::day_of_week>(src.day));
}

void copy_to(const comp::movable& src, protobuf::movable& dst)
{
  copy_to(src.position, dst.mutable_position());
  copy_to(src.velocity, dst.mutable_velocity());
  dst.set_speed(src.speed);
}

void copy_to(const comp::depth_drawable& src, protobuf::depth_drawable& dst)
{
  copy_to(src.src, dst.mutable_src());
  copy_to(src.dst, dst.mutable_dst());
  dst.set_texture_index(src.texture);
  dst.set_layer_index(src.layer);
  dst.set_depth_index(src.depth);
}

void copy_to(const comp::animated& src, protobuf::animated& dst)
{
  dst.set_frame(src.frame);
  dst.set_frame_count(src.frame_count);
  dst.set_then(src.then.count());
  dst.set_delay(src.delay.count());
}

void copy_to(const comp::plant& src, protobuf::plant& dst)
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

void copy_to(const comp::tile& src, protobuf::tile& dst)
{
  copy_to(src.src, dst.mutable_src());
  dst.set_id(src.id);
  dst.set_texture_index(src.texture);
  dst.set_depth_index(src.depth);
}

void copy_to(const comp::tilemap& src, protobuf::tilemap& dst)
{
  copy_to(src.size, dst.mutable_size());
  dst.set_id(src.id);
  dst.set_humanoid_layer_index(src.humanoid_layer);
  dst.set_row_count(src.row_count);
  dst.set_column_count(src.col_count);
}

void copy_to(const comp::tile_animation& src, protobuf::tile_animation& dst)
{
  dst.set_index(src.index);
  dst.set_then(src.then.count());

  for (const auto& frame : src.frames) {
    auto* frameData = dst.add_frames();
    frameData->set_tile_id(frame.tile);
    frameData->set_duration(frame.duration.count());
  }
}

void copy_to(const comp::chase& src, protobuf::chase& dst)
{
  dst.set_target_entity(entt::to_integral(src.target));
  dst.set_range(src.range);
  dst.set_is_active(src.active);
}

void copy_to(const comp::particle& src, protobuf::particle& dst)
{
  copy_to(src.position, dst.mutable_position());
  copy_to(src.acceleration, dst.mutable_acceleration());
  copy_to(src.color, dst.mutable_color());
  dst.set_now(src.now);
  dst.set_duration(src.duration);
}

void copy_to(const comp::point_light& src, protobuf::point_light& dst)
{
  copy_to(src.position, dst.mutable_position());
  dst.set_size(src.size);
  dst.set_fluctuation(src.fluctuation);
  dst.set_fluctuation_step(src.fluctuation_step);
  dst.set_fluctuation_limit(src.fluctuation_limit);
}

void copy_to(const comp::spawnpoint& src, protobuf::spawnpoint& dst)
{
  copy_to(src.position, dst.mutable_position());
  dst.set_type(static_cast<protobuf::spawnpoint_type>(src.type));
}

void copy_to(const comp::hitbox& src, protobuf::hitbox& dst)
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

void copy_to(const comp::object& src, protobuf::map_object& dst)
{
  dst.set_id(src.id);
}

void copy_to(const comp::portal& src, protobuf::portal& dst)
{
  if (src.target) {
    dst.set_map_id(*src.target);
  }
  dst.set_path(src.path);
}

void copy_to(const comp::tile_layer& src, protobuf::tile_layer& dst)
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

void copy_to(const comp::tileset& src, protobuf::tileset& dst)
{
  auto& map = *dst.mutable_tile_to_entity();
  for (const auto& [id, entity] : src.tiles) {
    map[id] = entt::to_integral(entity);
  }
}

void copy_to(const comp::inventory& src, protobuf::inventory& dst)
{
  dst.set_capacity(src.capacity);
  for (const auto entity : src.items) {
    dst.add_items(entt::to_integral(entity));
  }
}

void copy_to(const comp::tile_object& src, protobuf::tile_object& dst)
{
  dst.set_tile_entity(entt::to_integral(src.tile_entity));
}

void copy_to(const comp::trigger& src, protobuf::trigger& dst)
{
  dst.set_type(static_cast<protobuf::trigger_type>(src.type));
}

void copy_to(const comp::associated_entity& src, protobuf::associated_entity& dst)
{
  dst.set_entity(entt::to_integral(src.entity));
}

void save_level(const entt::registry& registry, protobuf::level* data)  // NOLINT
{
  registry.each([&](const entt::entity entity) {
    const auto value = entt::to_integral(entity);
    data->add_entities(value);

    if (registry.all_of<comp::player>(entity)) {
      assert(!data->has_player_entity());
      data->set_player_entity(value);
    }

    if (registry.all_of<comp::humanoid>(entity)) {
      data->add_humanoids(value);
    }

    if (const auto* movable = registry.try_get<comp::movable>(entity)) {
      copy_to(*movable, (*data->mutable_movables())[value]);
    }

    if (const auto* drawable = registry.try_get<comp::depth_drawable>(entity)) {
      copy_to(*drawable, (*data->mutable_drawables())[value]);
    }

    if (const auto* animated = registry.try_get<comp::animated>(entity)) {
      copy_to(*animated, (*data->mutable_animations())[value]);
    }

    if (const auto* plant = registry.try_get<comp::plant>(entity)) {
      copy_to(*plant, (*data->mutable_plants())[value]);
    }

    if (const auto* tile = registry.try_get<comp::tile>(entity)) {
      copy_to(*tile, (*data->mutable_tiles())[value]);
    }

    if (const auto* tilemap = registry.try_get<comp::tilemap>(entity)) {
      copy_to(*tilemap, (*data->mutable_tilemaps())[value]);
    }

    if (const auto* animation = registry.try_get<comp::tile_animation>(entity)) {
      copy_to(*animation, (*data->mutable_tile_animations())[value]);
    }

    if (const auto* chase = registry.try_get<comp::chase>(entity)) {
      copy_to(*chase, (*data->mutable_chases())[value]);
    }

    if (const auto* particle = registry.try_get<comp::particle>(entity)) {
      copy_to(*particle, (*data->mutable_particles())[value]);
    }

    if (const auto* light = registry.try_get<comp::point_light>(entity)) {
      copy_to(*light, (*data->mutable_lights())[value]);
    }

    if (const auto* spawnpoint = registry.try_get<comp::spawnpoint>(entity)) {
      copy_to(*spawnpoint, (*data->mutable_spawnpoints())[value]);
    }

    if (const auto* hitbox = registry.try_get<comp::hitbox>(entity)) {
      copy_to(*hitbox, (*data->mutable_hitboxes())[value]);
    }

    if (const auto* object = registry.try_get<comp::object>(entity)) {
      copy_to(*object, (*data->mutable_objects())[value]);
    }

    if (const auto* portal = registry.try_get<comp::portal>(entity)) {
      copy_to(*portal, (*data->mutable_portals())[value]);
    }

    if (const auto* layer = registry.try_get<comp::tile_layer>(entity)) {
      copy_to(*layer, (*data->mutable_tile_layers())[value]);
    }

    if (const auto* tileset = registry.try_get<comp::tileset>(entity)) {
      copy_to(*tileset, (*data->mutable_tilesets())[value]);
    }

    if (const auto* inventory = registry.try_get<comp::inventory>(entity)) {
      copy_to(*inventory, (*data->mutable_inventories())[value]);
    }

    if (const auto* object = registry.try_get<comp::tile_object>(entity)) {
      copy_to(*object, (*data->mutable_tile_objects())[value]);
    }

    if (const auto* trigger = registry.try_get<comp::trigger>(entity)) {
      copy_to(*trigger, (*data->mutable_triggers())[value]);
    }

    if (const auto* association = registry.try_get<comp::associated_entity>(entity)) {
      copy_to(*association, (*data->mutable_associations())[value]);
    }
  });

  const auto& viewport = registry.ctx<ctx::viewport>();
  data->set_is_outside_level(viewport.keep_in_bounds);
}

void save_shared_data(const entt::registry& shared, protobuf::shared_data* data)
{
  copy_to(shared.ctx<ctx::time_of_day>(), data->mutable_time());
}

void save_data(const entt::registry& shared, protobuf::save& save)
{
  save.set_current_level_id(sys::current_level(shared).id);
  save_shared_data(shared, save.mutable_shared());

  for (auto&& [entity, level] : shared.view<comp::level>().each()) {
    auto* data = save.add_levels();
    data->set_id(level.id);
    data->set_is_outside_level(shared.all_of<comp::outside_level>(entity));
    save_level(level.registry, data);
  }
}

}  // namespace

void save_shared_registry(const entt::registry& shared, const std::filesystem::path& path)
{
  std::ofstream stream{path, std::ios::out | std::ios::trunc | std::ios::binary};

  protobuf::save save;
  save_data(shared, save);

  if (!save.SerializeToOstream(&stream)) {
    CENTURION_LOG_ERROR("Something went wrong when trying to create a save file!");
  }
}

}  // namespace wanderer
