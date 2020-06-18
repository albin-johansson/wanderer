#include "render_movables_system.h"

#include "animated.h"
#include "depth_drawable.h"
#include "game_constants.h"
#include "movable.h"

using centurion::FArea;
using centurion::FRect;
using centurion::IRect;
using centurion::Renderer;

namespace wanderer::system {

inline constexpr FArea entitySize{g_entityDrawWidth, g_entityDrawHeight};

void render_movables(entt::registry& registry, Renderer& renderer)
{
  registry.sort<DepthDrawable>(
      [](const DepthDrawable& lhs, const DepthDrawable& rhs) noexcept {
        return lhs.depth < rhs.depth;
      });

  const auto entities = registry.view<DepthDrawable>();

  entities.each([&](const auto entity, const DepthDrawable& drawable) noexcept {
    if (const auto* movable = registry.try_get<Movable>(entity); movable) {
      const auto [x, y] = movable->interpolatedPos;
      const IRect src{{drawable.srcX, drawable.srcY}, {64, 64}};
      const FRect dst{{x, y}, entitySize};
      renderer.render_tf(*drawable.texture, src, dst);
    }
  });
}

}  // namespace wanderer::system
