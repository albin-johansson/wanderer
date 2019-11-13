#include "entity_moving_state.h"
#include "movable_delegate.h"
#include "entity_state_machine.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

EntityMovingState::EntityMovingState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
  animation.SetFrame(0);
  animation.SetNumberOfFrames(9);
  animation.SetDelay(75);
}

EntityMovingState::~EntityMovingState() = default;

void EntityMovingState::CheckPressed(const Input& input) {
  bool left = input.IsPressed(SDL_SCANCODE_A);
  bool right = input.IsPressed(SDL_SCANCODE_D);
  bool up = input.IsPressed(SDL_SCANCODE_W);
  bool down = input.IsPressed(SDL_SCANCODE_S);

  if (left && right) {
    entity->Stop(Direction::LEFT);
    entity->Stop(Direction::RIGHT);
  } else if (left) {
    entity->Move(Direction::LEFT);
  } else if (right) {
    entity->Move(Direction::RIGHT);
  }

  if (up && down) {
    entity->Stop(Direction::UP);
    entity->Stop(Direction::DOWN);
  } else if (up) {
    entity->Move(Direction::UP);
  } else if (down) {
    entity->Move(Direction::DOWN);
  }

  areMoveKeysDown = up || down || right || left;
}

void EntityMovingState::CheckReleased(const Input& input) {
  bool left = input.WasReleased(SDL_SCANCODE_A);
  bool right = input.WasReleased(SDL_SCANCODE_D);
  bool up = input.WasReleased(SDL_SCANCODE_W);
  bool down = input.WasReleased(SDL_SCANCODE_S);

  if (left) {
    entity->Stop(Direction::LEFT);
  }

  if (right) {
    entity->Stop(Direction::RIGHT);
  }

  if (up) {
    entity->Stop(Direction::UP);
  }

  if (down) {
    entity->Stop(Direction::DOWN);
  }
}

void EntityMovingState::Tick(float delta) {
  animation.Update();

  Vector2 velocity = entity->GetVelocity();
  entity->AddX(velocity.GetX() * delta);
  entity->AddY(velocity.GetY() * delta);
}

void EntityMovingState::Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept {
  Vector2 interpolatedPosition = entity->GetInterpolatedPosition();
  auto x = viewport.GetTranslatedX(interpolatedPosition.GetX());
  auto y = viewport.GetTranslatedY(interpolatedPosition.GetY());

  auto srcX = animation.GetIndex() * 64;

  if (entity->GetVelocity().IsZero()) {
    srcX = 0;
  }

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

  auto src = Rectangle(srcX, srcY, 64, 64);

  auto dst = Rectangle(x, y, entity->GetWidth(), entity->GetHeight());
  renderer.RenderTexture(entity->GetTileSheet().GetTexture(), src, dst);
}

void EntityMovingState::HandleInput(const Input& input) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(input);
  CheckReleased(input);

  // TODO check for attack

  if (!areMoveKeysDown && entity->GetVelocity().IsZero()) {
    parent->Change(EntityStateID::IDLE);
  }
}

void EntityMovingState::EnterState() {
}

void EntityMovingState::ExitState() {
}

}