#include "player_moving_state.h"
#include "entity_state_machine.h"
#include "entity.h"
#include "entity_sheet.h"
#include "require.h"
#include "input.h"
#include "wanderer_core.h"
#include "tile_map.h"
#include <SDL.h>

using namespace centurion;

namespace albinjohansson::wanderer {

PlayerMovingState::PlayerMovingState(IEntityStateMachine* parent)
    : moveDelegate(parent) {
  this->parent = Require::NotNull(parent);
}

PlayerMovingState::~PlayerMovingState() = default;

void PlayerMovingState::CheckPressed(const Input& input) {
  bool left = input.IsPressed(SDL_SCANCODE_A);
  bool right = input.IsPressed(SDL_SCANCODE_D);
  bool up = input.IsPressed(SDL_SCANCODE_W);
  bool down = input.IsPressed(SDL_SCANCODE_S);
  IEntity& entity = moveDelegate.GetParent().GetEntity();

  if (left && right) {
    entity.stop(Direction::Left);
    entity.stop(Direction::Right);
  } else if (left) {
    entity.move(Direction::Left);
  } else if (right) {
    entity.move(Direction::Right);
  }

  if (up && down) {
    entity.stop(Direction::Up);
    entity.stop(Direction::Down);
  } else if (up) {
    entity.move(Direction::Up);
  } else if (down) {
    entity.move(Direction::Down);
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
    entity.stop(Direction::Left);
  }

  if (right) {
    entity.stop(Direction::Right);
  }

  if (up) {
    entity.stop(Direction::Up);
  }

  if (down) {
    entity.stop(Direction::Down);
  }
}

void PlayerMovingState::HandleInput(const Input& input, const IWandererCore& core) {
  areMoveKeysDown = false; // assume no movement keys are down

  CheckPressed(input);
  CheckReleased(input);

  if (!areMoveKeysDown && moveDelegate.GetParent().GetEntity().get_velocity().IsZero()) {
    parent->SetState(EntityStateID::IDLE, core);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    parent->SetState(EntityStateID::ATTACK, core);
  }
}

void PlayerMovingState::Tick(const IWandererCore& core, float delta) {
  moveDelegate.Tick(core, delta);

  auto& player = moveDelegate.GetParent().GetEntity();

  if (core.get_active_map().IsBlocked(&player, delta)) {

    const auto& prevPos = player.get_previous_position();
    player.set_x(prevPos.x);
    player.set_y(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.GetParent().SetState(EntityStateID::IDLE, core);
    return;
  }
}

void PlayerMovingState::Draw(const Renderer& renderer, const Viewport& viewport) const noexcept {
  moveDelegate.Draw(renderer, viewport);
}

void PlayerMovingState::Exit(const IWandererCore& core) {
  moveDelegate.Exit(core);
}

void PlayerMovingState::Enter(const IWandererCore& core) {
  moveDelegate.Enter(core);
}

}