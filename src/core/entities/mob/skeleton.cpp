#include "skeleton.h"
#include "objects.h"
#include "skeleton_state_machine.h"

using namespace wanderer::visuals;

namespace wanderer::core {

Skeleton::Skeleton(Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  stateMachine = std::make_unique<SkeletonStateMachine>(this);
  movable = MovableObjectDelegate::Create(200, 200);
}

Skeleton::~Skeleton() = default;

void Skeleton::Draw(Renderer& renderer, const Viewport& viewport) const {
  stateMachine->Draw(renderer, viewport);
}

void Skeleton::Tick(const IGame& game, float delta) {
  movable->Tick(game, delta);
  stateMachine->Tick(game, delta);
}

}
