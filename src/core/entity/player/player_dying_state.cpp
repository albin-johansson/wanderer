#include "player_dying_state.h"

#include "entity.h"

using namespace centurion;

namespace wanderer {

PlayerDyingState::PlayerDyingState(IEntity* entity) : m_dyingDelegate(entity)
{}

PlayerDyingState::~PlayerDyingState() = default;

void PlayerDyingState::handle_input(const Input&, const IWandererCore&)
{}

void PlayerDyingState::draw(Renderer& renderer, const Viewport& viewport) const
{
  m_dyingDelegate.draw(renderer, viewport);
}

void PlayerDyingState::tick(const IWandererCore& core, float delta)
{
  m_dyingDelegate.tick(core, delta);
}

void PlayerDyingState::enter(const IWandererCore& core)
{
  m_dyingDelegate.enter(core);
}

void PlayerDyingState::exit(const IWandererCore& core)
{
  m_dyingDelegate.exit(core);
}

}  // namespace wanderer
