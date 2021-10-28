#include "menu_rendering_system.hpp"

#include "systems/ui/lazy-textures/lazy_texture_rendering_system.hpp"

#include "components/active_menu.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/graphics/render_text.hpp"
#include "core/resources.hpp"
#include "systems/ui/buttons/button_rendering_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/checkboxes/checkbox_rendering_system.hpp"
#include "systems/ui/grid.hpp"
#include "systems/ui/labels/label_rendering_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/lines/line_rendering_system.hpp"
#include "wanderer_std.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline const auto backdrop_path = resources::texture("backdrop.png");

void RenderTitle(const std::string& title,
                 const comp::MenuDrawable& drawable,
                 cen::renderer& renderer)
{
  if (title.empty()) {
    return;
  }

  if (!drawable.texture) {
    renderer.set_color(cen::colors::white);
    drawable.texture = RenderText(renderer, title, renderer.get_font(glob::menu_font_l));
  }

  const auto& texture = *drawable.texture;

  if (!drawable.position) {
    const auto x = static_cast<float>(CenterX(texture.width()));
    constexpr auto y = RowToY(2);
    drawable.position = {x, y};
  }

  renderer.render(texture, *drawable.position);
}

void RenderAuthorLabel(GraphicsContext& graphics)
{
  constexpr auto id = "developed_by_albin_johansson"_hs;

  auto& renderer = graphics.get_renderer();
  auto& cache = graphics.small_font_cache();

  if (!cache.has_stored(id)) {
    renderer.set_color(cen::colors::white);
    cache.store_blended_utf8(id, "Developed by Albin Johansson", renderer);
  }

  const auto& texture = cache.get_stored(id);
  const auto y = glob::logical_height<int> - texture.height() - glob::default_margin;
  renderer.render(texture, cen::point(glob::default_margin, y));
}

}  // namespace

void RenderActiveMenu(const entt::registry& shared)
{
  const auto menuEntity = shared.ctx<ctx::ActiveMenu>().entity;

  const auto& menu = shared.get<comp::Menu>(menuEntity);
  const auto& drawable = shared.get<comp::MenuDrawable>(menuEntity);

  auto& graphics = shared.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.get_renderer();

  if (menu.blocking) {
    const auto index = graphics.load("backdrop"_hs, backdrop_path);
    renderer.render(graphics[index], cen::irect{{}, glob::logical_size<>});
    renderer.fill_with(glob::transparent_black);
  }

  RenderLines(shared, graphics);
  RenderLazyTextures(shared, graphics);
  RenderButtonGroupIndicators(shared, graphics);
  RenderButtons(shared, graphics);
  RenderCheckboxes(shared, graphics);
  RenderLabels(shared, graphics);

  RenderTitle(menu.title, drawable, renderer);

  if (menu.blocking) {
    RenderAuthorLabel(graphics);
  }
}

}  // namespace wanderer::sys
