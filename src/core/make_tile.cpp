#include "make_tile.h"

#include "animated_tile.h"
#include "drawable.h"
#include "tile.h"

namespace wanderer {
namespace {

void add_animation(entt::registry& registry,
                   const entt::entity entity,
                   const step::Animation& stepAnimation)
{
  auto& animatedTile = registry.emplace<AnimatedTile>(entity);
  animatedTile.frame = 0;

  auto& frames = animatedTile.frames;
  frames.reserve(static_cast<std::size_t>(stepAnimation.length()));

  int index = 0;
  for (const auto& stepFrames : stepAnimation.frames()) {
    auto& frame = frames.at(static_cast<std::size_t>(index));
    frame.tile = static_cast<TileID>(stepFrames.tile_id());
    frame.duration = static_cast<u32>(stepFrames.duration());
    ++index;
  }
}

}  // namespace

entt::entity make_tile(entt::registry& registry, const step::Tile& stepTile)
{
  const auto entity{registry.create()};

  //  auto& tile = registry.emplace<Tile>(entity);
  //  tile.id = static_cast<TileID>(stepTile.id());
  //
  //  auto& drawable = registry.emplace<Drawable>(entity);
  //  drawable.texture = nullptr;
  //
  //  // TODO collision

  auto& tile = registry.emplace<Tile>(entity);
  tile.id = static_cast<TileID>(stepTile.id());

  if (const auto& stepAnimation = stepTile.animation(); stepAnimation) {
    add_animation(registry, entity, *stepAnimation);
  }

  const auto& tileProperties = stepTile.properties();
  if (tileProperties.has("depth")) {
    const auto& depthProp = tileProperties.get("depth");
  }

  //  const auto view = registry.view<Tile>();
  //  for (const auto e : view) {
  //    const auto& t = view.get<Tile>(e);
  //
  //    if (const auto* a = registry.try_get<AnimatedTile>(e); a) {
  //      // animated tile
  //    } else {
  //      // static tile
  //    }
  //  }

  return entity;
}

}  // namespace wanderer
