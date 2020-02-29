#include "menu_state_machine_impl.h"

#include <renderer.h>

#include "controls_menu.h"
#include "home_menu.h"
#include "in_game_menu.h"
#include "input.h"
#include "inventory_menu.h"
#include "menu.h"
#include "settings_menu.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

MenuStateMachineImpl::MenuStateMachineImpl(IWandererCore* core)
    : typewriterFonts("resources/font/type_writer.ttf")
{
  put(MenuID::Home, std::make_unique<HomeMenu>(this, core));
  put(MenuID::InGame, std::make_unique<InGameMenu>(this));
  put(MenuID::Settings, std::make_unique<SettingsMenu>(this));
  put(MenuID::Controls, std::make_unique<ControlsMenu>(this));
  put(MenuID::Inventory, std::make_unique<InventoryMenu>(this));
}

MenuStateMachineImpl::~MenuStateMachineImpl() = default;

void MenuStateMachineImpl::put(MenuID id, std::unique_ptr<IMenu> menu)
{
  menus.emplace(id, std::move(menu));
}

void MenuStateMachineImpl::draw(Renderer& renderer,
                                const Viewport& viewport) const
{
  menus.at(activeMenuID)->draw(renderer, viewport, typewriterFonts);
}

void MenuStateMachineImpl::set_menu(MenuID id) noexcept
{
  activeMenuID = id;
}

void MenuStateMachineImpl::handle_input(const Input& input) noexcept
{
  menus.at(activeMenuID)->handle_input(input);
}

const IMenu& MenuStateMachineImpl::get_menu() const
{
  return *menus.at(activeMenuID);
}

// FIXME problem with time based entities and blocking menus, where the NPC
// cooldowns are affected

}  // namespace albinjohansson::wanderer
