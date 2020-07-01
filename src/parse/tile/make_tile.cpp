#include "make_tile.h"

#include <log.h>
#include <timer.h>

#include "animated_tile.h"
#include "tile.h"

using namespace wanderer::comp;

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const Tile::entity tileEntity,
                   const step::Animation& stepAnimation,
                   const tile_id firstgid)
{
  auto& animatedTile = registry.emplace<AnimatedTile>(tileEntity.get());
  animatedTile.frame = 0;
  animatedTile.then = ctn::Timer::millis();

  animatedTile.frames.reserve(static_cast<std::size_t>(stepAnimation.length()));

  for (const auto& stepFrames : stepAnimation.frames()) {
    auto& frame = animatedTile.frames.emplace_back();
    frame.tile = firstgid + static_cast<tile_id>(stepFrames.tile_id());
    frame.duration = static_cast<u32>(stepFrames.duration());
  }

  animatedTile.frames.shrink_to_fit();
}

}  // namespace

void parse_special_tile(entt::registry& registry,
                        const Tile::entity tileEntity,
                        const step::Tile& stepTile,
                        const tile_id firstGID)
{
  if (const auto& stepAnimation = stepTile.animation(); stepAnimation) {
    add_animation(registry, tileEntity, *stepAnimation, firstGID);
  }

  //  const auto& tileProperties = stepTile.properties();
  //  if (tileProperties.has("depth")) {
  //  }
}

auto make_basic_tile(entt::registry& registry,
                     const tile_id id,
                     const entt::handle<ctn::Texture>& sheet,
                     const ctn::IRect& src) noexcept -> Tile::entity
{
  const auto tileEntity = registry.create();

  auto& tile = registry.emplace<Tile>(tileEntity);
  tile.id = id;
  tile.sheet = sheet;
  tile.src = src;

  return Tile::entity{tileEntity};
}

}  // namespace wanderer
