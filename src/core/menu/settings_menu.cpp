#include "settings_menu.h"
#include "input.h"
#include "renderer.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SettingsMenu::SettingsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

SettingsMenu::~SettingsMenu() noexcept = default;

void SettingsMenu::Draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle& fonts) const {
  AbstractMenu::Draw(renderer, viewport, fonts);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
//  renderer.RenderText("Settings", 500, 100);
}

void SettingsMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME);
  }
}

bool SettingsMenu::IsBlocking() const noexcept {
  return true;
}

}
