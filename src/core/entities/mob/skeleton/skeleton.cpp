#include "skeleton.h"
#include <utility>
#include "objects.h"
#include "skeleton_state_machine.h"

namespace albinjohansson::wanderer {

Skeleton::Skeleton(Image_sptr sheet) : AbstractEntity(std::move(sheet)) {
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
}

Skeleton::~Skeleton() = default;

void Skeleton::Draw(Renderer& renderer, const Viewport& viewport) const {
  stateMachine->Draw(renderer, viewport);
}

void Skeleton::Tick(IWandererCore& core, float delta) {
  AbstractEntity::Tick(core, delta);
  stateMachine->Tick(core, delta);
}

}
