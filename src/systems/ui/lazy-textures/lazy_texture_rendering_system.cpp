#include "lazy_texture_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/lazy_texture.hpp"
#include "systems/ui/grid.hpp"

namespace wanderer::sys {

void render_lazy_textures(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  const auto active = registry.ctx<const ctx::active_menu>().entity;

  const auto view =
      registry.view<const comp::lazy_texture, const comp::associated_menu>();
  for (auto&& [entity, lazy, associated] : view.each())
  {
    if (active.get() == associated.entity)
    {
      if (!lazy.texture)
      {
        lazy.texture = cen::texture{renderer, lazy.surface};
      }

      const auto position = from_grid(lazy.row, lazy.col);
      const auto& size = lazy.size;
      const auto rect = cen::rect(position.x(), position.y(), size.width, size.height);

      renderer.render(*lazy.texture, rect);
    }
  }
}

}  // namespace wanderer::sys
