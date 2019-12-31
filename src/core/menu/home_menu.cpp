#include "home_menu.h"
#include "require.h"
#include "input.h"

namespace albinjohansson::wanderer {

HomeMenu::HomeMenu(IMenuStateMachine* parent, IWandererCore* core) :
    AbstractMenu(parent),
    startButton("Start", 633, 250, 100, 40),
    settingsButton("Settings", 633, 320, 100, 40),
    controlsButton("Controls", 633, 390, 100, 40),
    quitButton("Quit", 633, 460, 100, 40) {
  this->core = Require::NotNull(core);
  fonts = std::make_unique<FontBundle>("resources/font/type_writer.ttf");
}

HomeMenu::~HomeMenu() noexcept = default;

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
    core->Quit(); // FIXME perhaps the core should look for quit flag from menus instead?
  }
}

void HomeMenu::Draw(Renderer& renderer, const Viewport& viewport, const FontBundle& fonts) const {
  AbstractMenu::Draw(renderer, viewport, fonts);

  startButton.Draw(renderer, viewport, fonts);
  settingsButton.Draw(renderer, viewport, fonts);
  controlsButton.Draw(renderer, viewport, fonts);
  quitButton.Draw(renderer, viewport, fonts);
}

}
