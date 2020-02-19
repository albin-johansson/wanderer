#include "in_game_menu.h"

#include "input.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

InGameMenu::InGameMenu(IMenuStateMachine* parent) : AbstractMenu(parent) {}

InGameMenu::~InGameMenu() = default;

void InGameMenu::draw(Renderer&, const Viewport&, const FontBundle&) const {}

void InGameMenu::handle_input(const Input& input) noexcept
{
  if (input.was_released(SDL_SCANCODE_ESCAPE)) {
    parent->set_menu(
        MenuID::Home);  // TODO need to stop any player movement here
  } else if (input.was_released(SDL_SCANCODE_I)) {
    parent->set_menu(MenuID::Inventory);
  }
}

bool InGameMenu::is_blocking() const noexcept { return false; }

}  // namespace albinjohansson::wanderer
