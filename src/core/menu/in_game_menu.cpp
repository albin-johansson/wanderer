#include "in_game_menu.h"
#include "input.h"

namespace albinjohansson::wanderer {

InGameMenu::InGameMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InGameMenu::~InGameMenu() = default;

void InGameMenu::Draw(Renderer&, const Viewport&, const FontBundle&) const {}

void InGameMenu::HandleInput(const wanderer::Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME); // TODO need to stop any player movement here
  } else if (input.WasReleased(SDL_SCANCODE_I)) {
    parent->SetMenu(MenuID::INVENTORY);
  }
}

bool InGameMenu::IsBlocking() const noexcept {
  return false;
}

}
