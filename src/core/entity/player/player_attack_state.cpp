#include "player_attack_state.h"

using namespace centurion;

namespace wanderer {

PlayerAttackState::PlayerAttackState(IEntityStateMachine* parent)
    : attackDelegate(parent)
{}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::HandleInput(const Input&, const IWandererCore&)
{}

void PlayerAttackState::draw(Renderer& renderer, const Viewport& viewport) const
{
  attackDelegate.draw(renderer, viewport);
}

void PlayerAttackState::tick(const IWandererCore& core, float delta)
{
  attackDelegate.tick(core, delta);
}

void PlayerAttackState::enter(const IWandererCore& core)
{
  attackDelegate.enter(core);
}

void PlayerAttackState::exit(const IWandererCore& core)
{
  attackDelegate.exit(core);
}

}  // namespace wanderer