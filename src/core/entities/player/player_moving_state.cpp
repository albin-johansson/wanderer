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
  this->parent = Require::not_null(parent);
}

PlayerMovingState::~PlayerMovingState() = default;

void PlayerMovingState::CheckPressed(const Input& input) {
  bool left = input.is_pressed(SDL_SCANCODE_A);
  bool right = input.is_pressed(SDL_SCANCODE_D);
  bool up = input.is_pressed(SDL_SCANCODE_W);
  bool down = input.is_pressed(SDL_SCANCODE_S);
  IEntity& entity = moveDelegate.GetParent().get_entity();

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
  bool left = input.was_released(SDL_SCANCODE_A);
  bool right = input.was_released(SDL_SCANCODE_D);
  bool up = input.was_released(SDL_SCANCODE_W);
  bool down = input.was_released(SDL_SCANCODE_S);
  auto& entity = moveDelegate.GetParent().get_entity();

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

  if (!areMoveKeysDown && moveDelegate.GetParent().get_entity().get_velocity().is_zero()) {
    parent->set_state(EntityStateID::Idle, core);
  } else if (input.is_pressed(SDL_SCANCODE_SPACE)) {
    parent->set_state(EntityStateID::Attack, core);
  }
}

void PlayerMovingState::tick(const IWandererCore& core, float delta) {
  moveDelegate.tick(core, delta);

  auto& player = moveDelegate.GetParent().get_entity();

  if (core.get_active_map().is_blocked(&player, delta)) {

    const auto& prevPos = player.get_previous_position();
    player.set_x(prevPos.x);
    player.set_y(prevPos.y);

    // TODO set position of entity to be next to the blocking object

    moveDelegate.GetParent().set_state(EntityStateID::Idle, core);
    return;
  }
}

void PlayerMovingState::draw(const Renderer& renderer, const Viewport& viewport) const noexcept {
  moveDelegate.draw(renderer, viewport);
}

void PlayerMovingState::exit(const IWandererCore& core) {
  moveDelegate.exit(core);
}

void PlayerMovingState::enter(const IWandererCore& core) {
  moveDelegate.enter(core);
}

}