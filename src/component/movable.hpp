#pragma once

#include "direction.hpp"
#include "vector2.hpp"

namespace wanderer::comp {

/**
 * @struct movable
 *
 * @brief Represents an entity that is movable.
 *
 * @note Whilst not required, movable components are expected to be drawable,
 * since the `interpolatedPos` member is solely intended for the rendered
 * position of the entity.
 *
 * @var movable::velocity
 * The current x- and y-axis speed.
 * @var movable::position
 * The current position.
 * @var movable::dominantDirection
 * The current dominant direction.
 * @var movable::speed
 * The current maximum total speed of the movable. This is used to make sure
 * that the movable doesn't move faster when traveling in more than one
 * direction.
 *
 * @headerfile movable.hpp
 */
struct movable final
{
  vector2f velocity;
  vector2f position;
  direction dominantDirection{direction::down};
  float speed{0};
};

}  // namespace wanderer::comp