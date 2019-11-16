#include "home_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::core {

HomeMenu::HomeMenu(IMenuStateMachine* parent) :
    AbstractMenu(parent),
    startButton(MenuButton("Start", 633, 250, 100, 40)),
    settingsButton("Settings", 633, 320, 100, 40),
    controlsButton("Controls", 633, 390, 100, 40),
    quitButton(MenuButton("Quit", 633, 460, 100, 40)) {
  this->parent = Objects::RequireNonNull(parent);
}

HomeMenu::~HomeMenu() noexcept = default;

IMenu_uptr HomeMenu::Create(IMenuStateMachine* parent) {
  return std::make_unique<HomeMenu>(parent);
}

void HomeMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::IN_GAME);
  }

  auto mx = input.GetMouseX();
  auto my = input.GetMouseY();
  bool leftReleased = input.WasLeftButtonReleased();

  if (leftReleased && startButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::IN_GAME);

  } else if (leftReleased && settingsButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::SETTINGS);

  } else if (leftReleased && controlsButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::CONTROLS);

  } else if (leftReleased && quitButton.Contains(mx, my)) {
    // TODO quit...
  }
}

void HomeMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  static bool first = true;

  if (first) {
    renderer.SetColor(0xFF, 0xFF, 0xFF);
    startButton.LoadTexture(renderer);
    settingsButton.LoadTexture(renderer);
    controlsButton.LoadTexture(renderer);
    quitButton.LoadTexture(renderer);
    first = false;
  }

  AbstractMenu::Draw(renderer, viewport);

  startButton.Draw(renderer, viewport);
  settingsButton.Draw(renderer, viewport);
  controlsButton.Draw(renderer, viewport);
  quitButton.Draw(renderer, viewport);
}

}
