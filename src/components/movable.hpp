#pragma once

#include "core/direction.hpp"
#include "wanderer_std.hpp"

namespace wanderer::comp {

/// \brief Represents an entity that is movable.
/// \ingroup components
struct Movable final
{
  float2 velocity;                 ///< Current x- and y-axis speed.
  float2 position;                 ///< Current position.
  Direction dir{Direction::Down};  ///< Current dominant direction.
  float speed{};                   ///< Current maximum total speed of the movable.
};

}  // namespace wanderer::comp