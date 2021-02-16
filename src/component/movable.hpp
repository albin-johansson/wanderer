#pragma once

#include "direction.hpp"
#include "vector2.hpp"

namespace wanderer::comp {

/**
 * \struct movable
 *
 * \brief Represents an entity that is movable.
 *
 * \headerfile movable.hpp
 */
struct movable final
{
  vector2f velocity;               ///< Current x- and y-axis speed.
  vector2f position;               ///< Current position.
  direction dir{direction::down};  ///< Current dominant direction.
  float speed{0};  ///< Current maximum total speed of the movable.
};

}  // namespace wanderer::comp