#pragma once

#include "core/direction.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Represents an entity that is movable.
/// \ingroup components
struct Movable final
{
  Vec2 velocity{};                 ///< Current x- and y-axis speed.
  Vec2 position{};                 ///< Current position.
  Direction dir{Direction::Down};  ///< Current dominant direction.
  float speed{};                   ///< Current maximum total speed of the movable.
};

}  // namespace wanderer