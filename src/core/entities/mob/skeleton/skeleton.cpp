#include "skeleton.h"
#include "skeleton_state_machine.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "objects.h"
#include <utility>

namespace albinjohansson::wanderer {

Skeleton::Skeleton(std::shared_ptr<Image> sheet) : AbstractEntity(std::move(sheet)) {
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
