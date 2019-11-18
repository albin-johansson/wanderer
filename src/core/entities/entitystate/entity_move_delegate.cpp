#include "entity_move_delegate.h"
#include "entity_sheet.h"
#include "objects.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityMoveDelegate::EntityMoveDelegate(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);
}

EntityMoveDelegate::~EntityMoveDelegate() = default;

void EntityMoveDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = entity->GetVelocity().IsZero() ? 0 : animation.GetIndex() * 64;
  auto srcY = EntitySheet::GetSourceY(512, entity->GetDominantDirection());
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityMoveDelegate::Tick(float delta) {
  animation.Update();

  Vector2 velocity = entity->GetVelocity();
  entity->AddX(velocity.GetX() * delta);
  entity->AddY(velocity.GetY() * delta);
}

void EntityMoveDelegate::Enter() {
  animation.SetFrame(0);
  animation.SetNumberOfFrames(9);
  animation.SetDelay(60);
}

void EntityMoveDelegate::Exit() {}

}
