#include "make_tile.hpp"

#include <cassert>  // assert
#include <cen/counter.hpp>

#include "centurion_utils.hpp"
#include "component/animated_tile.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "hitbox_system.hpp"

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const comp::tile::entity tileEntity,
                   const step::animation& stepAnimation,
                   const tile_id gid)
{
  auto& animatedTile = registry.emplace<comp::animated_tile>(tileEntity.get());
  animatedTile.index = 0;
  animatedTile.then = cen::counter::ticks();

  animatedTile.frames.reserve(
      static_cast<std::size_t>(stepAnimation.num_frames()));

  for (const auto& stepFrames : stepAnimation.frames()) {
    auto& frame = animatedTile.frames.emplace_back();
    frame.tile = gid;
    frame.duration = cen::milliseconds<u32>{stepFrames.duration()};
  }

  animatedTile.frames.shrink_to_fit();
}

void add_hitbox(entt::registry& registry,
                const comp::tile::entity tileEntity,
                const step::object& object)
{
  const vector2f offset{static_cast<float>(object.x()),
                        static_cast<float>(object.y())};

  const cen::farea size{static_cast<float>(object.width()),
                        static_cast<float>(object.height())};

  registry.emplace<comp::hitbox>(tileEntity.get(),
                                 sys::hitbox::create({{offset, size}}));
}

}  // namespace

void parse_fancy_tile(entt::registry& registry,
                      const comp::tile::entity tileEntity,
                      const step::tile& stepTile,
                      const tile_id gid)
{
  if (const auto& stepAnimation = stepTile.get_animation(); stepAnimation) {
    add_animation(registry, tileEntity, *stepAnimation, gid);
  }

  if (const auto* layer = stepTile.object_group()) {
    if (const auto* group = layer->try_as<step::object_group>()) {
      // Only allow one object per tile for now
      assert(group->objects().size() == 1);
      const auto& object = group->objects().at(0);
      if (object.type() == "Hitbox") {
        add_hitbox(registry, tileEntity, object);
      }
    }
  }
}

auto make_basic_tile(entt::registry& registry,
                     const tile_id id,
                     const texture_handle& sheet,
                     const cen::irect& src) noexcept -> comp::tile::entity
{
  const auto tileEntity = registry.create();

  auto& tile = registry.emplace<comp::tile>(tileEntity);
  tile.id = id;
  tile.sheet = sheet;
  tile.src = src;

  return comp::tile::entity{tileEntity};
}

}  // namespace wanderer
