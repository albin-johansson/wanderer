#include "skeleton.h"

#include <utility>
#include "objects.h"
#include "skeleton_state_machine.h"
;

namespace albinjohansson::wanderer {

Skeleton::Skeleton(Image_sptr sheet) : AbstractEntity(std::move(sheet)) {
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
}

Skeleton::~Skeleton() = default;

void Skeleton::Draw(Renderer& renderer, const Viewport& viewport) const {
  stateMachine->Draw(renderer, viewport);
}

void Skeleton::Tick(const IGame& game, float delta) {
  AbstractEntity::Tick(game, delta);
  stateMachine->Tick(game, delta);
}

}
