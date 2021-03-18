#include "menu_system.hpp"

#include <centurion.hpp>
#include <filesystem>

#include "button_system.hpp"
#include "cursors.hpp"
#include "files_directory.hpp"
#include "game_constants.hpp"
#include "menu_constants.hpp"
#include "parse_menu.hpp"
#include "render_text.hpp"
#include "saves_menu_system.hpp"
#include "switch_menu_event.hpp"

namespace wanderer::sys {
namespace {

void query_binds(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 comp::menu& menu,
                 const cen::key_state& keys)
{
  for (const auto entity : menu.binds)
  {
    auto& bind = registry.get<comp::key_bind>(entity);
    if (keys.was_just_released(bind.key))
    {
      if (bind.action)
      {
        bind.action->execute(dispatcher);
      }
    }
  }
}

void render_lines(const entt::registry& registry,
                  const comp::menu_drawable& drawable,
                  cen::renderer& renderer)
{
  renderer.set_color(cen::colors::white);

  for (const auto entity : drawable.lines)
  {
    const auto& line = registry.get<comp::line>(entity);
    renderer.draw_line(line.start, line.end);
  }
}

void render_labels(const entt::registry& registry,
                   const comp::menu_drawable& drawable,
                   cen::renderer& renderer)
{
  const auto& font = renderer.get_font(glob::menu_font_s);

  for (const auto entity : drawable.labels)
  {
    const auto& label = registry.get<comp::label>(entity);
    if (auto& texture = label.texture; !texture)
    {
      renderer.set_color(label.color);
      texture = render_text(renderer, label.text, font);
    }

    renderer.render(*label.texture, label.position);
  }
}

void render_title(const std::string& title,
                  const comp::menu_drawable& drawable,
                  cen::renderer& renderer)
{
  if (title.empty())
  {
    return;
  }

  if (auto& texture = drawable.titleTexture; !texture.has_value())
  {
    auto& font = renderer.get_font(glob::menu_font_l);

    renderer.set_color(cen::colors::white);
    texture = renderer.render_blended_utf8(title.c_str(), font);
  }

  const auto& texture = *drawable.titleTexture;

  if (!drawable.titlePos)
  {
    const auto x = (glob::logical_width<int> / 2) - (texture.width() / 2);
    const auto y = convert_row_to_y(2);
    drawable.titlePos = {x, y};
  }

  renderer.render<int>(texture, *drawable.titlePos);
}

}  // namespace

auto create_menus() -> entt::registry
{
  entt::registry registry;

  const auto home = parse_menu(registry, "resource/menu/home_menu.json");
  parse_menu(registry, "resource/menu/in_game_menu.json");
  parse_menu(registry, "resource/menu/settings_menu.json");
  parse_menu(registry, "resource/menu/controls_menu.json");
  create_saves_menu(registry);

  registry.emplace<comp::active_menu>(home);

  auto& cursors = registry.emplace<comp::cursors>(registry.create());
  cursors.data.try_emplace(cen::system_cursor::hand, cen::system_cursor::hand);

  return registry;
}

void update_menu(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const cen::mouse_state& mouseState,
                 const cen::key_state& keyState)
{
  const auto view = registry.view<comp::active_menu, comp::menu>();
  view.each([&](const entt::entity entity, comp::menu& menu) {
    const auto menuEntity = comp::menu::entity{entity};
    const auto button = update_button_hover(registry, menuEntity, mouseState);
    if (button)
    {
      query_button(registry, dispatcher, *button, mouseState);
    }
    else
    {
      cen::cursor::reset();
    }
    query_binds(registry, dispatcher, menu, keyState);
  });
}

void switch_menu(entt::registry& registry, const menu_id id)
{
  registry.clear<comp::active_menu>();

  const auto view = registry.view<comp::menu>();
  view.each([&](const entt::entity e, const comp::menu& menu) {
    if (menu.id == id)
    {
      registry.emplace<comp::active_menu>(e);

      if (menu.id == menu_id::saves)
      {
        refresh_saves_menu(registry);
      }
    }
  });
}

void render_menu(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::active_menu,
                                  const comp::menu,
                                  const comp::menu_drawable>();
  view.each([&](const comp::menu& menu, const comp::menu_drawable& drawable) {
    if (menu.blocking)
    {
      renderer.fill_with(glob::transparent_black);
    }

    render_lines(registry, drawable, renderer);
    render_labels(registry, drawable, renderer);

    for (const auto button : menu.buttons)
    {
      render_button(registry, button, renderer);
    }

    render_title(menu.title, drawable, renderer);
  });
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto view = registry.view<const comp::active_menu, const comp::menu>();
  return view.get<const comp::menu>(view.front()).blocking;
}

}  // namespace wanderer::sys
