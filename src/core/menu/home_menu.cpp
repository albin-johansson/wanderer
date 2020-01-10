#include "home_menu.h"
#include "require.h"
#include "input.h"

using namespace centurion;

namespace albinjohansson::wanderer {

HomeMenu::HomeMenu(IMenuStateMachine* parent, IWandererCore* core) :
    AbstractMenu(parent),
    startButton("Start", 633, 250, 100, 40),
    settingsButton("Settings", 633, 320, 100, 40),
    controlsButton("Controls", 633, 390, 100, 40),
    quitButton("Quit", 633, 460, 100, 40) {
  this->core = Require::not_null(core);
  fonts = std::make_unique<FontBundle>("resources/font/type_writer.ttf");
}

HomeMenu::~HomeMenu() noexcept = default;

void HomeMenu::handle_input(const Input& input) noexcept {
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(MenuID::InGame);
  }

  auto mx = input.get_mouse_x();
  auto my = input.get_mouse_y();
  bool leftReleased = input.was_left_button_released();

  startButton.SetEnlarged(!leftReleased && startButton.Contains(mx, my));
  settingsButton.SetEnlarged(!leftReleased && settingsButton.Contains(mx, my));
  controlsButton.SetEnlarged(!leftReleased && controlsButton.Contains(mx, my));
  quitButton.SetEnlarged(!leftReleased && quitButton.Contains(mx, my));

  if (leftReleased && startButton.Contains(mx, my)) {
    parent->set_menu(MenuID::InGame);

  } else if (leftReleased && settingsButton.Contains(mx, my)) {
    parent->set_menu(MenuID::Settings);

  } else if (leftReleased && controlsButton.Contains(mx, my)) {
    parent->set_menu(MenuID::Controls);

  } else if (leftReleased && quitButton.Contains(mx, my)) {
    core->quit(); // FIXME perhaps the core should look for quit flag from menus instead?
  }
}

void HomeMenu::draw(Renderer& renderer, const Viewport& viewport, const FontBundle& fonts) const {
  AbstractMenu::draw(renderer, viewport, fonts);

  startButton.draw(renderer, viewport, fonts);
  settingsButton.draw(renderer, viewport, fonts);
  controlsButton.draw(renderer, viewport, fonts);
  quitButton.draw(renderer, viewport, fonts);
}

}
