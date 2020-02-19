#include "controls_menu.h"

#include <renderer.h>

#include "input.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

ControlsMenu::ControlsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

ControlsMenu::~ControlsMenu() noexcept = default;

void ControlsMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const
{
  AbstractMenu::draw(renderer, viewport, fonts);

//  renderer.set_color(white);
  //  renderer.RenderText("Controls", 500, 100);
}

void ControlsMenu::handle_input(const Input& input) noexcept
{
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(MenuID::Home);
  }
}

}  // namespace albinjohansson::wanderer
