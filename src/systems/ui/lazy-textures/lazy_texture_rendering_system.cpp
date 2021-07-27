#include "lazy_texture_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/lazy_texture.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_lazy_textures(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  const auto active = registry.ctx<ctx::active_menu>().entity;

  for (auto&& [entity, lazy, associated] :
       registry.view<comp::lazy_texture, comp::associated_menu>().each())
  {
    if (active.get() == associated.entity)
    {
      if (!lazy.texture)
      {
        lazy.texture = cen::texture{renderer, lazy.surface};
      }

      const auto position = from_grid(lazy.position);
      const auto& size = lazy.size;
      const auto rect = cen::rect(position.x(), position.y(), size.width, size.height);

      renderer.render(*lazy.texture, rect);

      renderer.set_color(cen::colors::white);
      renderer.draw_rect(rect);
    }
  }
}

}  // namespace wanderer::sys
