#include "menu_manager.hpp"

#include "menus.hpp"

namespace wanderer {

menu_manager::menu_manager(const game_cfg& cfg)
{
  mMenus[menu_id::home] = make_main_menu(cfg);
  mMenus[menu_id::game] = make_in_game_menu(cfg);
}

void menu_manager::switch_to(const menu_id menu)
{
  mCurrentMenu = menu;
}

void menu_manager::poll(const input_state& input, entt::dispatcher& dispatcher)
{
  mMenus.at(mCurrentMenu).poll(input, dispatcher);
}

void menu_manager::render(graphics_ctx& graphics)
{
  mMenus.at(mCurrentMenu).render(graphics);
}

auto menu_manager::is_blocking() const -> bool
{
  return mMenus.at(mCurrentMenu).is_blocking();
}

}  // namespace wanderer