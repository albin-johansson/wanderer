#include "settings_menu.h"
#include "objects.h"

namespace wanderer::core {

SettingsMenu::SettingsMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

SettingsMenu::~SettingsMenu() noexcept = default;

IMenu_uptr SettingsMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<SettingsMenu>(parent);
}

void SettingsMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  AbstractMenu::Draw(renderer, viewport);

  renderer.SetColor(0xFF, 0xFF, 0xFF);
  renderer.RenderText("Settings", 500, 100);
}

void SettingsMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::HOME);
  }
}

}
