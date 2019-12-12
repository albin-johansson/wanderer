#include "entity_move_delegate.h"
#include "entity_sheet.h"
#include "objects.h"
#include "entity_draw_delegate.h"
#include "entity.h"
#include "wanderer_core.h"

namespace albinjohansson::wanderer {

EntityMoveDelegate::EntityMoveDelegate(IEntityStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

EntityMoveDelegate::~EntityMoveDelegate() = default;

void EntityMoveDelegate::Draw(Renderer& renderer, const Viewport& viewport) const {
  IEntity& entity = parent->GetEntity();

  auto srcX = entity.GetVelocity().IsZero() ? 0 : entity.GetAnimationFrame() * 64;
  auto srcY = EntitySheet::GetSourceY(512, entity.GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, entity, srcX, srcY);
}

void EntityMoveDelegate::Tick(const IWandererCore& core, float delta) {
  IEntity& entity = parent->GetEntity();

  entity.UpdateAnimation();

  auto[velocityX, velocityY] = entity.GetVelocity();
  entity.AddX(velocityX * delta);
  entity.AddY(velocityY * delta);

  // TODO collision detection
}

void EntityMoveDelegate::Enter(const IWandererCore& core) {
  IEntity& entity = parent->GetEntity();

  entity.SetAnimationFrame(0);
  entity.SetAnimationFrameAmount(9);
  entity.SetAnimationDelay(60);
}

void EntityMoveDelegate::Exit(const IWandererCore& core) {}

}
