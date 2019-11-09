#include "player_controller.h"
#include "objects.h"
#include "direction.h"

using namespace wanderer::core;

namespace wanderer::controller {

PlayerController::PlayerController(IWandererController* controller) {
  this->controller = Objects::RequireNonNull(controller);
}

PlayerController::~PlayerController() = default;

void PlayerController::CheckPressed(const KeyStateManager& keyStateManager) {
  bool left = keyStateManager.IsPressed(SDL_SCANCODE_A);
  bool right = keyStateManager.IsPressed(SDL_SCANCODE_D);
  bool up = keyStateManager.IsPressed(SDL_SCANCODE_W);
  bool down = keyStateManager.IsPressed(SDL_SCANCODE_S);

  if (left && right) {
    controller->StopPlayer(Direction::LEFT);
    controller->StopPlayer(Direction::RIGHT);
  } else if (left) {
    controller->MovePlayer(Direction::LEFT);
  } else if (right) {
    controller->MovePlayer(Direction::RIGHT);
  }

  if (up && down) {
    controller->StopPlayer(Direction::UP);
    controller->StopPlayer(Direction::DOWN);
  } else if (up) {
    controller->MovePlayer(Direction::UP);
  } else if (down) {
    controller->MovePlayer(Direction::DOWN);
  }
}

void PlayerController::CheckReleased(const KeyStateManager& keyStateManager) {
  bool left = keyStateManager.WasReleased(SDL_SCANCODE_A);
  bool right = keyStateManager.WasReleased(SDL_SCANCODE_D);
  bool up = keyStateManager.WasReleased(SDL_SCANCODE_W);
  bool down = keyStateManager.WasReleased(SDL_SCANCODE_S);

  if (left) {
    controller->StopPlayer(Direction::LEFT);
  }

  if (right) {
    controller->StopPlayer(Direction::RIGHT);
  }

  if (up) {
    controller->StopPlayer(Direction::UP);
  }

  if (down) {
    controller->StopPlayer(Direction::DOWN);
  }
}

void PlayerController::Update(const KeyStateManager& keyStateManager) {
  CheckPressed(keyStateManager);
  CheckReleased(keyStateManager);
}

}
