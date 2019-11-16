#include "in_game_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::core {

InGameMenu::InGameMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InGameMenu::~InGameMenu() = default;

IMenu_uptr InGameMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<InGameMenu>(parent);
}

void InGameMenu::Draw(visuals::Renderer& renderer, const core::Viewport& viewport) noexcept {}

void InGameMenu::HandleInput(const wanderer::core::Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME); // TODO need to stop any player movement here
  }
}

}
