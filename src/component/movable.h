#pragma once
#include "direction.h"
#include "types.h"

namespace wanderer {

struct Movable final {
  VectorF32 velocity;         // holds the current x- and y-speed
  VectorF32 currentPos;       // holds the current position
  VectorF32 oldPos;           // holds the previous position
  VectorF32 interpolatedPos;  // holds the interpolated previous position
  Direction dominantDirection{Direction::Down};  // holds the dominant direction
                                                 // of the movable
  f32 speed{0};  // holds the maximum possible total speed
};

}  // namespace wanderer