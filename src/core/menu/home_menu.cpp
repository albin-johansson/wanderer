#include "home_menu.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::core {

HomeMenu::HomeMenu(IMenuStateMachine* parent) :
    startButton(MenuButton("Start", 633, 250, 100, 40)),
    optionsButton("Options", 633, 320, 100, 40),
    controlsButton("Controls", 633, 390, 100, 40),
    quitButton(MenuButton("Quit", 633, 460, 100, 40)) {
  this->parent = Objects::RequireNonNull(parent);
}

HomeMenu::~HomeMenu() = default;

void HomeMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::IN_GAME);
  }

  auto mx = input.GetMouseX();
  auto my = input.GetMouseY();
  bool left = input.WasLeftButtonReleased();

  if (left && startButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::IN_GAME);
  } else if (left && quitButton.Contains(mx, my)) {
    // TODO quit...
  }
}

void HomeMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  static bool first = true;

  if (first) {
    renderer.SetColor(0xFF, 0xFF, 0xFF);
    startButton.LoadTexture(renderer);
    optionsButton.LoadTexture(renderer);
    controlsButton.LoadTexture(renderer);
    quitButton.LoadTexture(renderer);
    first = false;
  }

  auto bounds = viewport.GetBounds();
  renderer.SetColor(0, 0, 0, 0xAA);
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);

  startButton.Draw(renderer, viewport);
  optionsButton.Draw(renderer, viewport);
  controlsButton.Draw(renderer, viewport);
  quitButton.Draw(renderer, viewport);
}

}
