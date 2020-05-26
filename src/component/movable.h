#pragma once
#include <vector_2.h>

namespace wanderer {

struct Movable final {
  Vector2f velocity;         // holds the current x- and y-speed
  Vector2f currentPos;       // holds the current position
  Vector2f oldPos;           // holds the previous position
  Vector2f interpolatedPos;  // holds the interpolated previous position
  float speed;               // holds the maximum possible total speed
};

}  // namespace wanderer