#include "entity_dying_delegate.h"
#include "objects.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) const {
  auto srcX = entity->GetAnimationFrame() * 64;
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, 1280);
}

void EntityDyingDelegate::Tick(const IGame& game, float delta) {
  if (!entity->IsAnimationDone()) {
    entity->UpdateAnimation();
  }
}

void EntityDyingDelegate::Enter(const IGame& game) {
  entity->SetAnimationFrameAmount(6);
  entity->SetAnimationFrame(0);
  entity->SetAnimationDelay(65);
}

void EntityDyingDelegate::Exit(const IGame& game) {
  // TODO set entity to be dead
}

}
