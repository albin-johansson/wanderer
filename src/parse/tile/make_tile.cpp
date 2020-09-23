#include "make_tile.hpp"

#include <counter.hpp>
#include <log.hpp>

#include "animated_tile.hpp"
#include "tile.hpp"

using namespace wanderer::comp;

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const Tile::entity tileEntity,
                   const step::animation& stepAnimation,
                   const tile_id firstgid)
{
  auto& animatedTile = registry.emplace<AnimatedTile>(tileEntity.get());
  animatedTile.frame = 0;
  animatedTile.then = cen::counter::ticks().count();  // FIXME

  animatedTile.frames.reserve(
      static_cast<std::size_t>(stepAnimation.num_frames()));

  for (const auto& stepFrames : stepAnimation.frames()) {
    auto& frame = animatedTile.frames.emplace_back();
    frame.tile = firstgid + static_cast<tile_id>(stepFrames.tile_id().get());
    frame.duration = static_cast<u32>(stepFrames.duration());
  }

  animatedTile.frames.shrink_to_fit();
}

}  // namespace

void parse_special_tile(entt::registry& registry,
                        const Tile::entity tileEntity,
                        const step::tile& stepTile,
                        const tile_id firstGID)
{
  if (const auto& stepAnimation = stepTile.get_animation(); stepAnimation) {
    add_animation(registry, tileEntity, *stepAnimation, firstGID);
  }

  //  const auto& tileProperties = stepTile.properties();
  //  if (tileProperties.has("depth")) {
  //  }
}

auto make_basic_tile(entt::registry& registry,
                     const tile_id id,
                     const entt::handle<cen::texture>& sheet,
                     const cen::irect& src) noexcept -> Tile::entity
{
  const auto tileEntity = registry.create();

  auto& tile = registry.emplace<Tile>(tileEntity);
  tile.id = id;
  tile.sheet = sheet;
  tile.src = src;

  return Tile::entity{tileEntity};
}

}  // namespace wanderer
