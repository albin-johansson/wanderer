#include "entity_idle_state.h"
#include "entity_state_machine.h"
#include "objects.h"
#include "vector_2.h"

namespace wanderer::core {

EntityIdleState::EntityIdleState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

EntityIdleState::~EntityIdleState() = default;

void EntityIdleState::Tick(float delta) {
}

void EntityIdleState::HandleInput(const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    parent->Change(EntityStateID::WALK);
    return;
  }

  // TODO attack...
}

void EntityIdleState::EnterState() {
}

void EntityIdleState::ExitState() {
}

void EntityIdleState::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  Vector2 interpolatedPosition = entity->GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());

  float srcY;
  switch (entity->GetDominantDirection()) {
    case Direction::UP: {
      srcY = 512;
      break;
    }
    case Direction::RIGHT: {
      srcY = 704;
      break;
    }
    case Direction::DOWN: {
      srcY = 640;
      break;
    }
    case Direction::LEFT: {
      srcY = 576;
      break;
    }
  }

  auto src = Rectangle(0, srcY, 64, 64);
  auto dst = Rectangle(x, y, entity->GetWidth(), entity->GetHeight());
  renderer.RenderTexture(entity->GetTileSheet().GetTexture(), src, dst);
}

}
