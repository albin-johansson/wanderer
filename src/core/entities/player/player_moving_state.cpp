#include "player_moving_state.h"
#include "entity_state_machine.h"
#include "entity.h"
#include "entity_sheet.h"
#include "objects.h"
#include "input.h"
#include "wanderer_core.h"
#include "tile_map.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

PlayerMovingState::PlayerMovingState(IEntityStateMachine* parent)
    : moveDelegate(parent) {
  this->parent = Objects::RequireNonNull(parent);
}

PlayerMovingState::~PlayerMovingState() = default;

void PlayerMovingState::CheckPressed(const Input& input) {
  bool left = input.IsPressed(SDL_SCANCODE_A);
  bool right = input.IsPressed(SDL_SCANCODE_D);
  bool up = input.IsPressed(SDL_SCANCODE_W);
  bool down = input.IsPressed(SDL_SCANCODE_S);
  IEntity& entity = moveDelegate.GetParent().GetEntity();

  if (left && right) {
    entity.Stop(Direction::LEFT);
    entity.Stop(Direction::RIGHT);
  } else if (left) {
    entity.Move(Direction::LEFT);
  } else if (right) {
    entity.Move(Direction::RIGHT);
  }

  if (up && down) {
    entity.Stop(Direction::UP);
    entity.Stop(Direction::DOWN);
  } else if (up) {
    entity.Move(Direction::UP);
  } else if (down) {
    entity.Move(Direction::DOWN);
  }

  areMoveKeysDown = up || down || right || left;
}

void PlayerMovingState::CheckReleased(const Input& input) {
  bool left = input.WasReleased(SDL_SCANCODE_A);
  bool right = input.WasReleased(SDL_SCANCODE_D);
  bool up = input.WasReleased(SDL_SCANCODE_W);
  bool down = input.WasReleased(SDL_SCANCODE_S);
  auto& entity = moveDelegate.GetParent().GetEntity();

  if (left) {
    entity.Stop(Direction::LEFT);
  }

  if (right) {
    entity.Stop(Direction::RIGHT);
  }

  if (up) {
    entity.Stop(Direction::UP);
  }

  if (down) {
    entity.Stop(Direction::DOWN);
  }
}

void PlayerMovingState::HandleInput(const Input& input, const IWandererCore& core) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(input);
  CheckReleased(input);

  if (!areMoveKeysDown && moveDelegate.GetParent().GetEntity().GetVelocity().IsZero()) {
    parent->SetState(EntityStateID::IDLE, core);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    parent->SetState(EntityStateID::ATTACK, core);
  }
}

void PlayerMovingState::Tick(const IWandererCore& core, float delta) {
  moveDelegate.Tick(core, delta);

  auto& player = moveDelegate.GetParent().GetEntity();

  if (core.GetActiveMap().IsBlocked(&player, delta)) {

    const auto& prevPos = player.GetPreviousPosition();
    player.SetX(prevPos.x);
    player.SetY(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.GetParent().SetState(EntityStateID::IDLE, core);
    return;
  }
}

void PlayerMovingState::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  moveDelegate.Draw(renderer, viewport);
}

void PlayerMovingState::Exit(const IWandererCore& core) {
  moveDelegate.Exit(core);
}

void PlayerMovingState::Enter(const IWandererCore& core) {
  moveDelegate.Enter(core);
}

}