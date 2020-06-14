#include "make_tile.h"

#include <log.h>
#include <timer.h>

#include "animated_tile.h"
#include "drawable.h"
#include "tile.h"

using namespace centurion;

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const entt::entity tileEntity,
                   const step::Animation& stepAnimation,
                   const TileID firstgid)
{
  auto& animatedTile = registry.emplace<AnimatedTile>(tileEntity);
  animatedTile.frame = 0;
  animatedTile.then = Timer::millis();

  animatedTile.frames.reserve(static_cast<std::size_t>(stepAnimation.length()));

  for (const auto& stepFrames : stepAnimation.frames()) {
    auto& frame = animatedTile.frames.emplace_back();
    frame.tile = firstgid + static_cast<TileID>(stepFrames.tile_id());
    frame.duration = static_cast<u32>(stepFrames.duration());
  }

  animatedTile.frames.shrink_to_fit();
}

}  // namespace

void parse_special_tile(entt::registry& registry,
                        const entt::entity tileEntity,
                        const step::Tile& stepTile,
                        const TileID firstGID)
{
  if (const auto& stepAnimation = stepTile.animation(); stepAnimation) {
    add_animation(registry, tileEntity, *stepAnimation, firstGID);
  }

  //  const auto& tileProperties = stepTile.properties();
  //  if (tileProperties.has("depth")) {
  //  }
}

entt::entity make_basic_tile(entt::registry& registry,
                             const TileID id,
                             const std::shared_ptr<Texture>& sheet,
                             const IRect& src) noexcept
{
  const auto tileEntity = registry.create();

  auto& tile = registry.emplace<Tile>(tileEntity);
  tile.id = id;
  tile.sheet = sheet;
  tile.src = src;

  return tileEntity;
}

}  // namespace wanderer
