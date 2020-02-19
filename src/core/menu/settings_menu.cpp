#include "settings_menu.h"

#include "input.h"
#include "renderer.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

SettingsMenu::SettingsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

SettingsMenu::~SettingsMenu() noexcept = default;

void SettingsMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const
{
  AbstractMenu::draw(renderer, viewport, fonts);

//  renderer.set_color(white);
  //  renderer.RenderText("Settings", 500, 100);
}

void SettingsMenu::handle_input(const Input& input) noexcept
{
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(MenuID::Home);
  }
}

bool SettingsMenu::is_blocking() const noexcept { return true; }

}  // namespace albinjohansson::wanderer
