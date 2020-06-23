#include "render_movables_system.h"

#include "depth_drawable.h"
#include "movable.h"

using centurion::FArea;
using centurion::FRect;
using centurion::IRect;
using centurion::Renderer;

namespace wanderer::system {

void render_movables(entt::registry& registry, Renderer& renderer)
{
  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.sort<DepthDrawable>(
      [](const DepthDrawable& lhs, const DepthDrawable& rhs) noexcept {
        return (lhs.depth < rhs.depth ||
                (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY));
      });

  const auto entities = registry.view<DepthDrawable>();

  entities.each([&](const auto entity, const DepthDrawable& drawable) noexcept {
    if (const auto* movable = registry.try_get<Movable>(entity); movable) {
      const auto [x, y] = movable->interpolatedPos;
      const FRect dst{{x, y}, drawable.size};
      renderer.render_tf(*drawable.texture, drawable.src, dst);
    }
  });
}

}  // namespace wanderer::system
