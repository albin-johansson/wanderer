#include "entity_dying_delegate.h"
#include "entity.h"
#include "entity_draw_delegate.h"
#include "objects.h"

namespace albinjohansson::wanderer {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::Draw(Renderer& renderer, const Viewport& viewport) const {
  // TODO fade entity transparency after finishing animation
  auto srcX = entity->GetAnimationFrame() * 64;
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, 1280);
}

void EntityDyingDelegate::Tick(const IWandererCore& core, float delta) {
  if (!entity->IsAnimationDone()) {
    entity->UpdateAnimation();
  }
}

void EntityDyingDelegate::Enter(const IWandererCore& core) {
  entity->SetAnimationFrameAmount(6);
  entity->SetAnimationFrame(0);
  entity->SetAnimationDelay(65);
}

void EntityDyingDelegate::Exit(const IWandererCore& core) {
  // TODO set entity to be dead
}

}
