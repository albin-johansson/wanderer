/**
 * @brief Provides the `Movable` component.
 * @file movable.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.h"
#include "vector_2.h"

namespace wanderer::comp {

/**
 * @struct Movable
 * @brief Represents an entity that is movable.
 *
 * @note Whilst not required, movable components are expected to be drawable,
 * since the `interpolatedPos` member is solely intended for the rendered
 * position of the entity.
 *
 * @var Movable::velocity
 * The current x- and y-axis speed.
 * @var Movable::currentPos
 * The current position.
 * @var Movable::oldPos
 * The old position from the previous iteration.
 * @var Movable::interpolatedPos
 * The interpolated position from the previous and current position. This is
 * intended to be used as the position where the movable is rendered.
 * @var Movable::dominantDirection
 * The current dominant direction.
 * @var Movable::speed
 * The current maximum total speed of the movable. This is used to make sure
 * that the movable doesn't move faster when traveling in more than one
 * direction.
 *
 * @headerfile movable.h
 */
struct Movable final {
  Vector2f velocity;
  Vector2f currentPos;
  Vector2f oldPos;
  Vector2f interpolatedPos;
  Direction dominantDirection{Direction::Down};
  float speed{0};
};

}  // namespace wanderer::comp