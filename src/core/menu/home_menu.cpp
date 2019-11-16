#include "home_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::core {

HomeMenu::HomeMenu(IMenuStateMachine* parent)
    : startButton(MenuButton("Start", 500, 500, 150, 100)) {
  this->parent = Objects::RequireNonNull(parent);
}

HomeMenu::~HomeMenu() = default;

void HomeMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::IN_GAME);
  }

  if (input.WasLeftButtonReleased() && startButton.Contains(input.GetMouseX(), input.GetMouseY())) {
    parent->SetMenu(MenuID::IN_GAME);
  }
}

void HomeMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  static bool first = true;

  if (first) {
    startButton.LoadTexture(renderer);
    first = false;
  }

  auto bounds = viewport.GetBounds();
  renderer.SetColor(0, 0, 0, 0xAA);
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
  renderer.RenderText("Main menu", 100, 100);

  startButton.Draw(renderer, viewport);
}

}
