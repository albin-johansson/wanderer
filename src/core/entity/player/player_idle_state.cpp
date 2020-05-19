#include "player_idle_state.h"

#include "entity.h"
#include "entity_state_machine.h"
#include "input.h"

using namespace centurion;

namespace wanderer {

PlayerIdleState::PlayerIdleState(IEntityStateMachine* parent)
    : m_idleDelegate{parent}
{}

PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::handle_input(const Input& input,
                                   const IWandererCore& core)
{
  if (input.is_pressed(SDL_SCANCODE_D) || input.is_pressed(SDL_SCANCODE_A) ||
      input.is_pressed(SDL_SCANCODE_W) || input.is_pressed(SDL_SCANCODE_S)) {
    m_idleDelegate.get_parent().set_state(EntityStateID::Walk, core);
  } else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
    m_idleDelegate.get_parent().set_state(EntityStateID::Attack, core);
  } else if (input.is_pressed(SDL_SCANCODE_U)) {
    m_idleDelegate.get_parent().set_state(EntityStateID::Die, core);
  }

  // TODO attack...
}

void PlayerIdleState::draw(Renderer& renderer,
                           const Viewport& viewport) const noexcept
{
  m_idleDelegate.draw(renderer, viewport);
}

void PlayerIdleState::tick(const IWandererCore& core, float delta)
{
  m_idleDelegate.tick(core, delta);
}

void PlayerIdleState::enter(const IWandererCore& core)
{
  m_idleDelegate.enter(core);
}

void PlayerIdleState::exit(const IWandererCore& core)
{
  m_idleDelegate.exit(core);
}

}  // namespace wanderer
