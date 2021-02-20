#include "menu_system.hpp"

#include "cursors.hpp"
#include "game_constants.hpp"
#include "menu_constants.hpp"
#include "parse_menu.hpp"
#include "quit_event.hpp"
#include "registry_utils.hpp"
#include "switch_menu_event.hpp"

namespace wanderer::sys {
namespace {

void perform_action(entt::dispatcher& dispatcher, const menu_action action)
{
  switch (action) {
    case menu_action::quit: {
      dispatcher.enqueue<comp::quit_event>();
      break;
    }
    case menu_action::goto_in_game: {
      dispatcher.enqueue<comp::switch_menu_event>(menu_id::in_game);
      break;
    }
    case menu_action::goto_home: {
      dispatcher.enqueue<comp::switch_menu_event>(menu_id::home);
      break;
    }
    case menu_action::goto_settings: {
      dispatcher.enqueue<comp::switch_menu_event>(menu_id::settings);
      break;
    }
    case menu_action::goto_saves: {
      dispatcher.enqueue<comp::switch_menu_event>(menu_id::saves);
      break;
    }
    case menu_action::goto_controls: {
      dispatcher.enqueue<comp::switch_menu_event>(menu_id::controls);
      break;
    }
  }
}

void query_buttons(entt::registry& registry,
                   entt::dispatcher& dispatcher,
                   comp::menu& menu,
                   const cen::mouse_state& mouseState)
{
  auto& cursors = singleton<comp::cursors>(registry);
  auto& hand = cursors.data.at(cen::system_cursor::hand);

  maybe<menu_action> action;
  const auto mousePos = cen::cast<cen::fpoint>(mouseState.mouse_pos());
  bool hover{};

  for (auto& button : menu.buttons) {
    if (button.contains(mousePos)) {
      hover = true;
      button.set_hover(true);
      if (mouseState.was_left_button_released()) {
        action = button.action();
      }
    } else {
      button.set_hover(false);
    }
  }

  if (hover) {
    hand.enable();
  } else {
    cen::cursor::reset();
  }

  if (action) {
    perform_action(dispatcher, *action);
  }
}

void query_binds(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 comp::menu& menu,
                 const cen::key_state& keyState)
{
  for (const auto& bind : menu.binds) {
    if (keyState.was_just_released(bind.key)) {
      perform_action(dispatcher, bind.action);
    }
  }
}

void render_title(const comp::menu& menu, cen::renderer& renderer)
{
  const auto& texture = menu.titleTexture.value();

  if (!menu.titlePos) {
    const auto x = (glob::logicalWidth<int> / 2) - (texture.width() / 2);
    const auto y = glob::menuRowSize * 2;
    menu.titlePos = {x, y};
  }

  renderer.render<int>(texture, *menu.titlePos);
}

}  // namespace

auto create_menus() -> entt::registry
{
  entt::registry registry;
  const auto home = registry.create();

  registry.emplace<comp::menu>(home,
                               parse_menu("resource/menu/home_menu.json"));
  registry.emplace<comp::menu>(registry.create(),
                               parse_menu("resource/menu/in_game_menu.json"));
  registry.emplace<comp::menu>(registry.create(),
                               parse_menu("resource/menu/settings_menu.json"));
  registry.emplace<comp::menu>(registry.create(),
                               parse_menu("resource/menu/controls_menu.json"));
  registry.emplace<comp::menu>(registry.create(),
                               parse_menu("resource/menu/saves_menu.json"));

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
  view.each([&](comp::menu& menu) {
    query_buttons(registry, dispatcher, menu, mouseState);
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
  const auto view = registry.view<const comp::active_menu, const comp::menu>();
  view.each([&](const comp::menu& menu) {
    if (menu.blocking) {
      renderer.fill_with(glob::transparentBlack);
    }

    for (const auto& button : menu.buttons) {
      button.render(renderer);
    }

    if (menu.title.empty()) {
      return;  // nothing more to do if there is no title
    }

    if (!menu.titleTexture) {
      auto& font = renderer.get_font(glob::menuMediumFont);
      renderer.set_color(cen::colors::white);
      menu.titleTexture =
          renderer.render_blended_utf8(menu.title.c_str(), font);
    }

    render_title(menu, renderer);
  });
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto view = registry.view<const comp::active_menu, const comp::menu>();
  return view.get<const comp::menu>(view.front()).blocking;
}

}  // namespace wanderer::sys
