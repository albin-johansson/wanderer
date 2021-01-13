#include "make_tile.hpp"

#include <cassert>  // assert
#include <cen/counter.hpp>

#include "animated_tile.hpp"
#include "depth_drawable.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const comp::tile::entity tileEntity,
                   const step::animation& animation,
                   const tile_id firstGid)
{
  auto& tile = registry.emplace<comp::animated_tile>(tileEntity);
  auto& frames = tile.frames;

  tile.index = 0;
  tile.then = cen::counter::ticks();

  frames.reserve(static_cast<std::size_t>(animation.num_frames()));
  for (const auto& stepFrame : animation.frames()) {
    auto& frame = frames.emplace_back();
    frame.tile = firstGid + static_cast<tile_id>(stepFrame.tile_id().get());
    frame.duration = ms_t{stepFrame.duration()};
  }
}

void add_hitbox(entt::registry& registry,
                const comp::tile::entity tileEntity,
                const step::object& object)
{
  const vector2f offset{static_cast<float>(object.x()),
                        static_cast<float>(object.y())};

  const cen::farea size{static_cast<float>(object.width()),
                        static_cast<float>(object.height())};

  registry.emplace<comp::hitbox>(tileEntity,
                                 sys::hitbox::create({{offset, size}}));
}

[[nodiscard]] auto parse_depth(const step::properties& props) -> maybe<depth_t>
{
  if (props.has("depth")) {
    assert(props.get("depth").is<int>());
    return depth_t{props.get("depth").get<int>()};
  } else {
    return std::nullopt;
  }
}

}  // namespace

void parse_fancy_tile(entt::registry& registry,
                      const comp::tile::entity tileEntity,
                      const step::tile& stepTile,
                      const tile_id firstGid)
{
  if (const auto& stepAnimation = stepTile.get_animation()) {
    add_animation(registry, tileEntity, *stepAnimation, firstGid);
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

  if (const auto* props = stepTile.get_properties()) {
    if (const auto depth = parse_depth(*props)) {
      auto& tile = registry.get<comp::tile>(tileEntity);
      tile.depth = *depth;
    }
  }
}

auto make_basic_tile(entt::registry& registry,
                     const tile_id id,
                     const texture_handle& sheet,
                     const cen::irect& src) noexcept -> comp::tile::entity
{
  const comp::tile::entity entity{registry.create()};

  auto& tile = registry.emplace<comp::tile>(entity);
  tile.id = id;
  tile.sheet = sheet;
  tile.src = src;

  return entity;
}

}  // namespace wanderer
