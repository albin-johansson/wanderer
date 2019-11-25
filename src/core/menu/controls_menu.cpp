#include "controls_menu.h"
;

namespace albinjohansson::wanderer {

ControlsMenu::ControlsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

ControlsMenu::~ControlsMenu() noexcept = default;

IMenu_uptr ControlsMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<ControlsMenu>(parent);
}

void ControlsMenu::Draw(Renderer& renderer, const Viewport& viewport, FontBundle& fonts) const {
  AbstractMenu::Draw(renderer, viewport, fonts);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
//  renderer.RenderText("Controls", 500, 100);
}

void ControlsMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME);
  }
}

}
