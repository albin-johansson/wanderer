#include "menu_state_machine_impl.h"
#include "home_menu.h"
#include "in_game_menu.h"
#include "settings_menu.h"
#include "controls_menu.h"
#include "inventory_menu.h"

namespace albinjohansson::wanderer {

MenuStateMachineImpl::MenuStateMachineImpl(IWandererCore* core)
    : typewriterFonts("resources/font/type_writer.ttf") {

  Put(MenuID::HOME, HomeMenu::Create(this, core));
  Put(MenuID::IN_GAME, InGameMenu::Create(this));
  Put(MenuID::SETTINGS, SettingsMenu::Create(this));
  Put(MenuID::CONTROLS, ControlsMenu::Create(this));
  Put(MenuID::INVENTORY, std::make_unique<InventoryMenu>(this));
}

MenuStateMachineImpl::~MenuStateMachineImpl() = default;

IMenuStateMachine_uptr MenuStateMachineImpl::Create(IWandererCore* core) {
  return std::make_unique<MenuStateMachineImpl>(core);
}

void MenuStateMachineImpl::Put(MenuID id, IMenu_uptr menu) {
  menus.insert(std::pair<MenuID, IMenu_uptr>(id, std::move(menu)));
}

void MenuStateMachineImpl::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  menus.at(activeMenuID)->Draw(renderer, viewport);
}

void MenuStateMachineImpl::SetMenu(MenuID id) noexcept {
  activeMenuID = id;
}

void MenuStateMachineImpl::HandleInput(const Input& input) noexcept {
  menus.at(activeMenuID)->HandleInput(input);
}

// FIXME problem with time based entities and blocking menus, where the NPC cooldowns are affected
bool MenuStateMachineImpl::IsBlocking() const noexcept {
  return menus.at(activeMenuID)->IsBlocking();
}

}
