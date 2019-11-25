#include "in_game_menu.h"
#include "objects.h"

namespace albinjohansson::wanderer {

InGameMenu::InGameMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InGameMenu::~InGameMenu() = default;

IMenu_uptr InGameMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<InGameMenu>(parent);
}

void InGameMenu::Draw(Renderer& renderer,
                      const Viewport& viewport,
                      FontBundle& fonts) const {}

void InGameMenu::HandleInput(const wanderer::Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME); // TODO need to stop any player movement here
  } else if (input.WasReleased(SDL_SCANCODE_I)) {
    parent->SetMenu(MenuID::INVENTORY);
  }
}

}
