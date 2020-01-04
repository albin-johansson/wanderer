#include "settings_menu.h"
#include "input.h"
#include "renderer.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SettingsMenu::SettingsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

SettingsMenu::~SettingsMenu() noexcept = default;

void SettingsMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const {
  AbstractMenu::draw(renderer, viewport, fonts);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
//  renderer.RenderText("Settings", 500, 100);
}

void SettingsMenu::handle_input(const Input& input) noexcept {
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(MenuID::HOME);
  }
}

bool SettingsMenu::is_blocking() const noexcept {
  return true;
}

}
