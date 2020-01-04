#include "menu_state_machine_impl.h"
#include "wanderer_core.h"
#include "menu.h"
#include "viewport.h"
#include "input.h"
#include "renderer.h"
#include "home_menu.h"
#include "in_game_menu.h"
#include "settings_menu.h"
#include "controls_menu.h"
#include "inventory_menu.h"

using namespace centurion;

namespace albinjohansson::wanderer {

MenuStateMachineImpl::MenuStateMachineImpl(IWandererCore* core)
    : typewriterFonts("resources/font/type_writer.ttf") {

  Put(MenuID::HOME, std::make_unique<HomeMenu>(this, core));
  Put(MenuID::IN_GAME, std::make_unique<InGameMenu>(this));
  Put(MenuID::SETTINGS, std::make_unique<SettingsMenu>(this));
  Put(MenuID::CONTROLS, std::make_unique<ControlsMenu>(this));
  Put(MenuID::INVENTORY, std::make_unique<InventoryMenu>(this));
}

MenuStateMachineImpl::~MenuStateMachineImpl() = default;

void MenuStateMachineImpl::Put(MenuID id, std::unique_ptr<IMenu> menu) {
  menus.emplace(id, std::move(menu));
}

void MenuStateMachineImpl::Draw(Renderer& renderer, const Viewport& viewport) const {
  menus.at(activeMenuID)->Draw(renderer, viewport, typewriterFonts);
}

void MenuStateMachineImpl::SetMenu(MenuID id) noexcept {
  activeMenuID = id;
}

void MenuStateMachineImpl::HandleInput(const Input& input) noexcept {
  menus.at(activeMenuID)->HandleInput(input);
}

const IMenu& MenuStateMachineImpl::GetMenu() const {
  return *menus.at(activeMenuID);
}

// FIXME problem with time based entities and blocking menus, where the NPC cooldowns are affected

}
