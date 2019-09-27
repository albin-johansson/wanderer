#include "player.h"

namespace wanderer::model {

void Player::Update(double delta) {
//  position.SetX(speed.GetX() * delta);
}

void Player::Move(const Direction& dir) {
  switch (dir) {
    case Direction::UP: {
      speed.SetX(0);
      speed.SetY(-MOV_SPEED);
      break;
    }
    case Direction::RIGHT: {
      speed.SetX(MOV_SPEED);
      speed.SetY(0);
      break;
    }
    case Direction::DOWN: {
      speed.SetX(0);
      speed.SetY(MOV_SPEED);
      break;
    }
    case Direction::LEFT: {
      speed.SetX(-MOV_SPEED);
      speed.SetY(0);
      break;
    }
  }
}

}