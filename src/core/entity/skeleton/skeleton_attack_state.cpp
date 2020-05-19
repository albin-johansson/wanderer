#include "skeleton_attack_state.h"

#include "entity_state_machine.h"
#include "player.h"
#include "wanderer_core.h"

using namespace centurion;

namespace wanderer {

SkeletonAttackState::SkeletonAttackState(IEntityStateMachine* parent)
    : attackDelegate{parent}
{}

SkeletonAttackState::~SkeletonAttackState() = default;

void SkeletonAttackState::draw(Renderer& renderer,
                               const Viewport& viewport) const
{
  attackDelegate.draw(renderer, viewport);
}

void SkeletonAttackState::enter(const IWandererCore& core)
{
  attackDelegate.enter(core);
}

void SkeletonAttackState::exit(const IWandererCore& core)
{
  attackDelegate.exit(core);
}

void SkeletonAttackState::tick(const IWandererCore& core, float delta)
{
  attackDelegate.tick(core, delta);

  //    entity.SetDominantDirection(Direction::RIGHT);
  // TODO update dominant direction
}

}  // namespace wanderer
