#include "entity_dying_delegate.h"
#include "objects.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

EntityDyingDelegate::EntityDyingDelegate(IEntity* entity) {
  this->entity = Objects::RequireNonNull(entity);
}

EntityDyingDelegate::~EntityDyingDelegate() = default;

void EntityDyingDelegate::Draw(visuals::Renderer& renderer, const Viewport& viewport) {
  auto srcX = animation.GetIndex() * 64;
  EntityDrawDelegate::Draw(renderer, viewport, *entity, srcX, 1280);
}

void EntityDyingDelegate::Tick(float delta) {
  if (!animation.IsDone()) {
    animation.Update();
  }
}

void EntityDyingDelegate::Enter() {
  animation.SetNumberOfFrames(6);
  animation.SetFrame(0);
  animation.SetDelay(65);
}

void EntityDyingDelegate::Exit() {
  // TODO set entity to be dead
}

}
