#include "inventory_menu.h"
#include "input.h"

namespace albinjohansson::wanderer {

InventoryMenu::InventoryMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InventoryMenu::~InventoryMenu() = default;

void InventoryMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE) || input.WasReleased(SDL_SCANCODE_I)) {
    parent->SetMenu(MenuID::IN_GAME);
  }
}

bool InventoryMenu::IsBlocking() const noexcept { return true; }

}
