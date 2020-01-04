#include "controls_menu.h"
#include "input.h"
#include "renderer.h"

using namespace centurion;

namespace albinjohansson::wanderer {

ControlsMenu::ControlsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

ControlsMenu::~ControlsMenu() noexcept = default;

void ControlsMenu::Draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const {
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
