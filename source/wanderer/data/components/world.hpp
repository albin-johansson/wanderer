#pragma once

#include <box2d/box2d.h>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief Component featured by all physical objects in the game world.
 */
struct game_object final
{
  [[deprecated]] glm::vec2 position{};  ///< The position in screen coordinates.
  glm::vec2 size{};                     ///< The size of the object.
};

/**
 * \brief Component featured by all entities that are a part of the physics simulation.
 */
struct physics_body final
{
  b2Body* data{};       ///< The simulation body data.
  b2Vec2 size{};        ///< The size of the body, in simulation scale.
  float32 max_speed{};  ///< Maximum total speed, in simulation scale.
};

/**
 * \brief Context component representing the physics simulation.
 */
struct physics_world final
{
  /**
   * \brief The physics simulation world.
   */
  b2World simulation{{0, 0}};

  /**
   * \brief Scaling required to go from logical coordinates to simulation coordinates.
   */
  glm::vec2 scale{};
};

/// \} End of group components

}  // namespace wanderer::comp