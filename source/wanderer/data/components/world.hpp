#pragma once

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

/**
 * \brief Component featured by all physical objects in the game world.
 */
struct game_object final
{
  glm::vec2 position{};  ///< The position in world coordinates.
  glm::vec2 size{};      ///< The size of the object.
};

/**
 * \brief Component featured by all movable game objects.
 */
struct movable final
{
  glm::vec2 velocity{};  ///< The current velocity.
  float32 max_speed{};   ///< Maximum total speed.
};

}  // namespace wanderer::comp