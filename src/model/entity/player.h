#pragma once
#include "vector_2.h"
#include "direction.h"

namespace wanderer::model {

class Player final {
 private:
  static constexpr int MOV_SPEED = 5;

  Vector2 position;
  Vector2 speed;
  int width;
  int height;

 public:
  Player(int x, int y, int width, int height) : width(width), height(height) {
    position.SetX(x);
    position.SetY(y);
  }

  ~Player() = default;

  void Update(double delta);

  void Move(const Direction& dir);

};

}