#include "player_dying_state.h"

#include "entity.h"

using namespace centurion;

namespace wanderer {

PlayerDyingState::PlayerDyingState(IEntity* entity) : dyingDelegate(entity)
{}

PlayerDyingState::~PlayerDyingState() = default;

void PlayerDyingState::HandleInput(const Input&, const IWandererCore&)
{}

void PlayerDyingState::draw(Renderer& renderer, const Viewport& viewport) const
{
  dyingDelegate.draw(renderer, viewport);
}

void PlayerDyingState::tick(const IWandererCore& core, float delta)
{
  dyingDelegate.tick(core, delta);
}

void PlayerDyingState::enter(const IWandererCore& core)
{
  dyingDelegate.enter(core);
}

void PlayerDyingState::exit(const IWandererCore& core)
{
  dyingDelegate.exit(core);
}

}  // namespace wanderer
