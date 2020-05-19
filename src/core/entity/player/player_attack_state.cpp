#include "player_attack_state.h"

using namespace centurion;

namespace wanderer {

PlayerAttackState::PlayerAttackState(IEntityStateMachine* parent)
    : m_attackDelegate(parent)
{}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::handle_input(const Input&, const IWandererCore&)
{}

void PlayerAttackState::draw(Renderer& renderer, const Viewport& viewport) const
{
  m_attackDelegate.draw(renderer, viewport);
}

void PlayerAttackState::tick(const IWandererCore& core, float delta)
{
  m_attackDelegate.tick(core, delta);
}

void PlayerAttackState::enter(const IWandererCore& core)
{
  m_attackDelegate.enter(core);
}

void PlayerAttackState::exit(const IWandererCore& core)
{
  m_attackDelegate.exit(core);
}

}  // namespace wanderer
