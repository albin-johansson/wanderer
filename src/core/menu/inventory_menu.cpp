#include "inventory_menu.h"
#include "input.h"

namespace albinjohansson::wanderer {

InventoryMenu::InventoryMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InventoryMenu::~InventoryMenu() = default;

void InventoryMenu::handle_input(const Input& input) noexcept {
  if (input.was_released(SDL_SCANCODE_ESCAPE) || input.was_released(SDL_SCANCODE_I)) {
    parent->set_menu(MenuID::IN_GAME);
  }
}

bool InventoryMenu::is_blocking() const noexcept { return true; }

}
