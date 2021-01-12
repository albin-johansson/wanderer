#include "menu_manager.hpp"

#include <string_view>  // string_view

#include "game_constants.hpp"
#include "parse_menu.hpp"

namespace wanderer {

menu_manager::menu_manager() : m_current{menu_id::home}
{
  using namespace std::string_view_literals;

  m_menus.emplace(menu_id::home, parse_menu("resource/menu/home_menu.json"sv));
  m_menus.emplace(menu_id::in_game,
                  parse_menu("resource/menu/in_game_menu.json"sv));
  m_menus.emplace(menu_id::controls,
                  parse_menu("resource/menu/controls_menu.json"sv));
  m_menus.emplace(menu_id::settings,
                  parse_menu("resource/menu/settings_menu.json"sv));
}

void menu_manager::update(const cen::mouse_state& mouseState,
                          const cen::key_state& keyState,
                          cursor_manager& cursors)
{
  auto& menu = active_menu();

  if (const auto action = menu.query_buttons(mouseState, cursors)) {
    perform_action(*action);
  }

  if (const auto action = menu.query_binds(keyState)) {
    perform_action(*action);
  }
}

void menu_manager::render(cen::renderer& renderer)
{
  renderer.fill_with(glob::transparentBlack);

  auto& menu = active_menu();
  menu.render(renderer);
}

void menu_manager::switch_to(const menu_id menu)
{
  if (m_current != menu) {
    m_current = menu;
  }
}

void menu_manager::perform_action(const menu_action action)
{
  switch (action) {
    case menu_action::quit: {
      m_shouldQuit = true;
      break;
    }
    case menu_action::goto_in_game: {
      switch_to(menu_id::in_game);
      break;
    }
    case menu_action::goto_home: {
      switch_to(menu_id::home);
      break;
    }
    case menu_action::goto_settings: {
      switch_to(menu_id::settings);
      break;
    }
    case menu_action::goto_controls: {
      switch_to(menu_id::controls);
      break;
    }
  }
}

}  // namespace wanderer
