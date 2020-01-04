#include "controls_menu.h"
#include "input.h"
#include "renderer.h"

using namespace centurion;

namespace albinjohansson::wanderer {

ControlsMenu::ControlsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

ControlsMenu::~ControlsMenu() noexcept = default;

void ControlsMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const {
  AbstractMenu::draw(renderer, viewport, fonts);

  renderer.set_color(0xFF, 0xFF, 0xFF);
//  renderer.RenderText("Controls", 500, 100);
}

void ControlsMenu::handle_input(const Input& input) noexcept {
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(MenuID::HOME);
  }
}

}
