#include "home_menu.h"
#include "objects.h"

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::core {

HomeMenu::HomeMenu(IMenuStateMachine* parent, IWandererCore* core) :
    AbstractMenu(parent),
    startButton("Start", 633, 250, 100, 40),
    settingsButton("Settings", 633, 320, 100, 40),
    controlsButton("Controls", 633, 390, 100, 40),
    quitButton("Quit", 633, 460, 100, 40) {
  this->core = Objects::RequireNonNull(core);
  fonts = FontBundle::Create("resources/font/type_writer.ttf");
}

HomeMenu::~HomeMenu() noexcept = default;

IMenu_uptr HomeMenu::Create(IMenuStateMachine* parent, IWandererCore* core) {
  return std::make_unique<HomeMenu>(parent, core);
}

void HomeMenu::HandleInput(const Input& input) noexcept {
  if (input.WasReleased(SDL_SCANCODE_ESCAPE)) {
    parent->SetMenu(MenuID::IN_GAME);
  }

  auto mx = input.GetMouseX();
  auto my = input.GetMouseY();
  bool leftReleased = input.WasLeftButtonReleased();

  startButton.SetEnlarged(!leftReleased && startButton.Contains(mx, my));
  settingsButton.SetEnlarged(!leftReleased && settingsButton.Contains(mx, my));
  controlsButton.SetEnlarged(!leftReleased && controlsButton.Contains(mx, my));
  quitButton.SetEnlarged(!leftReleased && quitButton.Contains(mx, my));

  if (leftReleased && startButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::IN_GAME);

  } else if (leftReleased && settingsButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::SETTINGS);

  } else if (leftReleased && controlsButton.Contains(mx, my)) {
    parent->SetMenu(MenuID::CONTROLS);

  } else if (leftReleased && quitButton.Contains(mx, my)) {
    core->Quit();
  }
}

void HomeMenu::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  AbstractMenu::Draw(renderer, viewport);

  startButton.Draw(renderer, *fonts);
  settingsButton.Draw(renderer, *fonts);
  controlsButton.Draw(renderer, *fonts);
  quitButton.Draw(renderer, *fonts);
}

}
