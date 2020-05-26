#include "player_input.h"
#include "player.h"

namespace wanderer {

void PlayerInput::update(Registry& registry, const Input& input)
{
  const auto view = registry.view<Player>();

  registry.view<Player>().;

  if (input.is_pressed(SDL_SCANCODE_D) || input.is_pressed(SDL_SCANCODE_A) ||
      input.is_pressed(SDL_SCANCODE_W) || input.is_pressed(SDL_SCANCODE_S)) {
//    m_idleDelegate.get_parent().set_state(EntityStateID::Walk, core);
  } else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
//    m_idleDelegate.get_parent().set_state(EntityStateID::Attack, core);
  } else if (input.is_pressed(SDL_SCANCODE_U)) {
//    m_idleDelegate.get_parent().set_state(EntityStateID::Die, core);
  }

}

}
