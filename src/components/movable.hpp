#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/float2.hpp"
#include "core/aliases/ints.hpp"
#include "core/direction.hpp"

namespace wanderer::comp {
namespace detail {
struct movable_entity;
}

/**
 * \struct movable
 *
 * \brief Represents an entity that is movable.
 *
 * \headerfile movable.hpp
 */
struct movable final
{
  using entity = entity_type<detail::movable_entity>;

  float2 velocity;                 ///< Current x- and y-axis speed.
  float2 position;                 ///< Current position.
  direction dir{direction::down};  ///< Current dominant direction.
  float speed{0};                  ///< Current maximum total speed of the movable.
};

void serialize(auto& archive, movable& m, u32 version)
{
  archive(m.velocity, m.position, m.dir, m.speed);
}

}  // namespace wanderer::comp