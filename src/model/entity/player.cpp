#include "player.h"

namespace wanderer::model {

void Player::Update(double delta) {
  position.SetX(static_cast<int>(position.GetX() + (speed.GetX() * delta)));
  position.SetY(static_cast<int>(position.GetY() + (speed.GetY() * delta)));
}

void Player::Move(Direction direction) {
  switch (direction) {
    case Direction::UP: {
      speed.SetY(-MOV_SPEED);
      break;
    }
    case Direction::RIGHT: {
      speed.SetX(MOV_SPEED);
      break;
    }
    case Direction::DOWN: {
      speed.SetY(MOV_SPEED);
      break;
    }
    case Direction::LEFT: {
      speed.SetX(-MOV_SPEED);
      break;
    }
  }
}

void Player::Stop(Direction direction) {
  switch (direction) {
    case Direction::UP:
    case Direction::DOWN: {
      speed.SetY(0);
      break;
    }
    case Direction::RIGHT:
    case Direction::LEFT: {
      speed.SetX(0);
      break;
    }
  }
}

}