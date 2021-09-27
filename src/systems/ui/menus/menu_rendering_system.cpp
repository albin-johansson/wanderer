#include "menu_rendering_system.hpp"

#include "components/ctx/active_menu.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/checkbox.hpp"
#include "components/ui/menu.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/render_text.hpp"
#include "core/resources.hpp"
#include "systems/ui/buttons/button_rendering_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/checkboxes/checkbox_rendering_system.hpp"
#include "systems/ui/grid.hpp"
#include "systems/ui/labels/label_rendering_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/lazy-textures/lazy_texture_rendering_system.hpp"
#include "systems/ui/lines/line_rendering_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline const auto backdrop_path = resources::texture("backdrop.png");

void render_title(const std::string& title,
                  const comp::menu_drawable& drawable,
                  cen::renderer& renderer)
{
  if (title.empty()) {
    return;
  }

  if (!drawable.texture) {
    renderer.set_color(cen::colors::white);
    drawable.texture = render_text(renderer, title, renderer.get_font(glob::menu_font_l));
  }

  const auto& texture = *drawable.texture;

  if (!drawable.position) {
    const auto x = static_cast<float>(center_x(texture.width()));
    constexpr auto y = row_to_y(2);
    drawable.position = {x, y};
  }

  renderer.render(texture, *drawable.position);
}

void render_author_label(graphics_context& graphics)
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

void render_active_menu(const entt::registry& registry, graphics_context& graphics)
{
  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;

  const auto& menu = registry.get<comp::menu>(menuEntity);
  const auto& drawable = registry.get<comp::menu_drawable>(menuEntity);

  auto& renderer = graphics.get_renderer();

  if (menu.blocking) {
    const auto index = graphics.load(texture_id{"backdrop"_hs}, backdrop_path);
    renderer.render(graphics[index], cen::irect{{}, glob::logical_size<>});
    renderer.fill_with(glob::transparent_black);
  }

  render_lines(registry, graphics);
  render_lazy_textures(registry, graphics);
  render_button_group_indicators(registry, graphics);
  render_buttons(registry, graphics);
  render_checkboxes(registry, graphics);
  render_labels(registry, graphics);

  render_title(menu.title, drawable, renderer);

  if (menu.blocking) {
    render_author_label(graphics);
  }
}

}  // namespace wanderer::sys
