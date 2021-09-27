#pragma once

#include "common/entity_type.hpp"
#include "common/float2.hpp"
#include "common/ints.hpp"
#include "core/direction.hpp"

namespace wanderer::comp {

namespace tags {
struct movable_tag;
}  // namespace tags

/**
 * \struct movable
 *
 * \brief Represents an entity that is movable.
 *
 * \headerfile movable.hpp
 */
struct movable final
{
  using entity = entity_type<tags::movable_tag>;

  float2 velocity;                 ///< Current x- and y-axis speed.
  float2 position;                 ///< Current position.
  direction dir{direction::down};  ///< Current dominant direction.
  float speed{};                   ///< Current maximum total speed of the movable.
};

void serialize(auto& archive, movable& m, uint32 version)
{
  archive(m.velocity, m.position, m.dir, m.speed);
}

}  // namespace wanderer::comp