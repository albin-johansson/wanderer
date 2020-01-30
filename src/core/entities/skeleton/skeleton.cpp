#include "skeleton.h"
#include <image.h>
#include <renderer.h>
#include "skeleton_state_machine.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Skeleton::Skeleton(const shared<Image>& sheet) : AbstractEntity(sheet) {
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
}

Skeleton::~Skeleton() = default;

void Skeleton::init() {
  set_speed(GameConstants::mob_speed);
}

void Skeleton::draw(const Renderer& renderer, const Viewport& viewport) const {
  stateMachine->draw(renderer, viewport);
}

void Skeleton::tick(IWandererCore& core, float delta) {
  AbstractEntity::tick(core, delta);
  stateMachine->tick(core, delta);
}

}
