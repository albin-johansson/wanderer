#include "lazy_texture_rendering_system.hpp"

#include "components/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/lazy_texture.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void RenderLazyTextures(const entt::registry& registry, GraphicsContext& graphics)
{
  auto& renderer = graphics.get_renderer();
  const auto active = registry.ctx<ctx::ActiveMenu>().entity;

  for (auto&& [entity, lazy, associated] :
       registry.view<comp::LazyTexture, comp::AssociatedMenu>().each())
  {
    if (active == associated.entity) {
      if (!lazy.texture) {
        lazy.texture = cen::texture{renderer, lazy.surface};
      }

      const auto position = FromGrid(lazy.position);
      const auto& size = lazy.size;
      const auto rect = cen::rect(position.x(), position.y(), size.width, size.height);

      renderer.render(*lazy.texture, rect);

      renderer.set_color(cen::colors::white);
      renderer.draw_rect(rect);
    }
  }
}

}  // namespace wanderer::sys
