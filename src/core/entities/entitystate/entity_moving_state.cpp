#include "entity_moving_state.h"
#include "movable_delegate.h"
#include "entity_state_machine.h"
#include "objects.h"
#include "entity_sheet.h"

using namespace wanderer::visuals;

namespace wanderer::core {

EntityMovingState::EntityMovingState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
  animation.SetFrame(0);
  animation.SetNumberOfFrames(9);
  animation.SetDelay(60);
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

void EntityMovingState::Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept {
  auto srcX = (entity->GetVelocity().IsZero()) ? 0 : animation.GetIndex() * 64;
  auto srcY = EntitySheet::GetSourceY(512, entity->GetDominantDirection());
  drawDelegate.Draw(renderer, viewport, *entity, srcX, srcY);
}

void EntityMovingState::HandleInput(const Input& input) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(input);
  CheckReleased(input);

  if (!areMoveKeysDown && entity->GetVelocity().IsZero()) {
    parent->Change(EntityStateID::IDLE);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    parent->Change(EntityStateID::ATTACK);
  }
}

void EntityMovingState::Enter() {
  animation.SetFrame(0);
}

void EntityMovingState::Exit() {
}

}