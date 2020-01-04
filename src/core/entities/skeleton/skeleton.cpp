#include "skeleton.h"
#include "skeleton_state_machine.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Skeleton::Skeleton(const std::shared_ptr<Image>& sheet) : AbstractEntity(sheet) {
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
}

Skeleton::~Skeleton() = default;

void Skeleton::Init() {
  set_speed(mobSpeed);
}

void Skeleton::Draw(const Renderer& renderer, const Viewport& viewport) const {
  stateMachine->Draw(renderer, viewport);
}

void Skeleton::tick(IWandererCore& core, float delta) {
  AbstractEntity::tick(core, delta);
  stateMachine->Tick(core, delta);
}

}
