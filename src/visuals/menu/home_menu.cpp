#include "home_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::visuals {

HomeMenu::HomeMenu(IMenuStateMachine* parent)
    : startButton(MenuButton(100, 100, 200, 200)) {
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

void HomeMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  renderer.SetColor(0, 0, 0, 0xAA);

  auto bounds = viewport.GetBounds();
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);

  renderer.SetColor(0xFF, 0, 0);
  renderer.RenderFillRect(50, 50, 100, 100);

  startButton.Draw(renderer, viewport);
}

}
