#include "entity_dying_delegate.h"
#include "entity.h"
#include "entity_draw_delegate.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity) {
  this->entity = Require::NotNull(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::Draw(const Renderer& renderer, const Viewport&) const {
  // TODO fade entity transparency after finishing animation
  auto srcX = entity->GetAnimationFrame() * 64;
  EntityDrawDelegate::Draw(renderer, *entity, srcX, 1280);
}

void EntityDyingDelegate::Tick(const IWandererCore&, float /*delta*/) {
  if (!entity->IsAnimationDone()) {
    entity->UpdateAnimation();
  }
}

void EntityDyingDelegate::Enter(const IWandererCore&) {
  entity->SetAnimationFrameAmount(6);
  entity->SetAnimationFrame(0);
  entity->SetAnimationDelay(65);
}

void EntityDyingDelegate::Exit(const IWandererCore&) {
  // TODO set entity to be dead
}

}
