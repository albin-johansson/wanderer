#include "controls_menu.h"

using namespace wanderer::visuals;

namespace wanderer::core {

ControlsMenu::ControlsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

ControlsMenu::~ControlsMenu() noexcept = default;

IMenu_uptr ControlsMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<ControlsMenu>(parent);
}

void ControlsMenu::Draw(Renderer& renderer, const Viewport& viewport) {
  AbstractMenu::Draw(renderer, viewport);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
  renderer.RenderText("Controls", 500, 100);
}

void ControlsMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME);
  }
}

}
