#include "menu_state_machine_impl.h"
#include "home_menu.h"
#include "in_game_menu.h"

namespace wanderer::core {

MenuStateMachineImpl::MenuStateMachineImpl() {
  menus.insert(std::pair<MenuID, IMenu_sptr>(MenuID::HOME, std::make_shared<HomeMenu>(this)));
  menus.insert(std::pair<MenuID, IMenu_sptr>(MenuID::IN_GAME, std::make_shared<InGameMenu>(this)));

  activeMenu = menus.at(MenuID::HOME);
}

MenuStateMachineImpl::~MenuStateMachineImpl() = default;

void MenuStateMachineImpl::Draw(visuals::Renderer& renderer,
                                const core::Viewport& viewport) const noexcept {
  activeMenu->Draw(renderer, viewport);
}

void MenuStateMachineImpl::SetMenu(MenuID id) noexcept {
  activeMenu = menus.at(id);
}

MenuID MenuStateMachineImpl::GetActiveMenuID() const noexcept {
  return MenuID::HOME; // TODO give getter to menus
}

void MenuStateMachineImpl::HandleInput(const core::Input& input) noexcept {
  activeMenu->HandleInput(input);
}

bool MenuStateMachineImpl::IsBlocking() const noexcept {
  return activeMenu->IsBlocking();
}

}
