#include "render_depth_drawables_system.h"

#include "depth_drawable.h"

using centurion::Renderer;

namespace wanderer::system {

void render_depth_drawables(entt::registry& registry, Renderer& renderer)
{
  // TODO could have movables signal events when they have moved to check if
  //  they are within the viewport bounds and therefore should be rendered,
  //  this would make it possible to have a "InBounds" component

  registry.sort<DepthDrawable >(
      [](const DepthDrawable& lhs, const DepthDrawable& rhs) noexcept {
        return lhs.depth < rhs.depth ||
               (rhs.depth >= lhs.depth && lhs.centerY < rhs.centerY);
      },
      entt::insertion_sort{});

  registry.view<DepthDrawable>().each(
      [&renderer](const DepthDrawable& drawable) noexcept {
        renderer.render_tf(*drawable.texture, drawable.src, drawable.dst);
      });
}

}  // namespace wanderer::system
