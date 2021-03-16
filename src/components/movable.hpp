#pragma once

#include "direction.hpp"
#include "ints.hpp"
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
  float2 velocity;               ///< Current x- and y-axis speed.
  float2 position;               ///< Current position.
  direction dir{direction::down};  ///< Current dominant direction.
  float speed{0};  ///< Current maximum total speed of the movable.
};

template <typename Archive>
void serialize(Archive& archive, movable& m, u32 version)
{
  archive(m.velocity, m.position, m.dir, m.speed);
}

}  // namespace wanderer::comp