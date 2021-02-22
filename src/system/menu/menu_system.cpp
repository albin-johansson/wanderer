#include "menu_system.hpp"

#include "button_system.hpp"
#include "cursors.hpp"
#include "game_constants.hpp"
#include "menu_constants.hpp"
#include "parse_menu.hpp"
#include "switch_menu_event.hpp"

namespace wanderer::sys {
namespace {

void query_binds(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 comp::menu& menu,
                 const cen::key_state& keyState)
{
  for (const auto entity : menu.binds) {
    auto& bind = registry.get<comp::key_bind>(entity);
    if (keyState.was_just_released(bind.key)) {
      if (bind.action) {
        bind.action->execute(dispatcher);
      }
    }
  }
}

void render_title(const comp::menu_drawable& drawable, cen::renderer& renderer)
{
  const auto& texture = drawable.titleTexture.value();

  if (!drawable.titlePos) {
    const auto x = (glob::logicalWidth<int> / 2) - (texture.width() / 2);
    const auto y = glob::menuRowSize * 2;
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
  parse_menu(registry, "resource/menu/saves_menu.json");

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
    if (const auto button = update_button_hover(registry,
                                                comp::menu::entity{entity},
                                                mouseState)) {
      query_button(registry, dispatcher, mouseState, *button);
    } else {
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
    if (menu.id == id) {
      registry.emplace<comp::active_menu>(e);
    }
  });
}

void render_menu(const entt::registry& registry, cen::renderer& renderer)
{
  const auto view = registry.view<const comp::active_menu,
                                  const comp::menu,
                                  const comp::menu_drawable>();
  view.each([&](const comp::menu& menu, const comp::menu_drawable& drawable) {
    if (menu.blocking) {
      renderer.fill_with(glob::transparentBlack);
    }

    for (const auto entity : menu.buttons) {
      render_button(registry, renderer, entity);
    }

    if (menu.title.empty()) {
      return;  // nothing more to do if there is no title
    }

    if (auto& texture = drawable.titleTexture; !texture.has_value()) {
      auto& font = renderer.get_font(glob::menuMediumFont);

      renderer.set_color(cen::colors::white);
      texture = renderer.render_blended_utf8(menu.title.c_str(), font);
    }

    render_title(drawable, renderer);
  });
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto view = registry.view<const comp::active_menu, const comp::menu>();
  return view.get<const comp::menu>(view.front()).blocking;
}

}  // namespace wanderer::sys
