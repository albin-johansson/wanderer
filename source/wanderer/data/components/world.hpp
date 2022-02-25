#pragma once

#include <box2d/box2d.h>
#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/data/day.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief Component featured by all physical objects in the game world.
 */
struct game_object final
{
  glm::vec2 position{};  ///< The position in logical coordinates.
  glm::vec2 size{};      ///< The size of the object.
};

/**
 * \brief Component featured by all entities that are a part of the physics simulation.
 */
struct physics_body final
{
  b2Body* data{};       ///< The simulation body data.
  b2Vec2 offset{};      ///< Body offset from the game object origin, in simulation scale.
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

/**
 * \brief Context component that provides information about the in-game date and time.
 */
struct date_and_time final
{
  float32 hour{};                        ///< [0, 24)
  float32 minute{};                      ///< [0, 60)
  float32 seconds{};                     ///< Reset once per in-game day.
  int32 week{};                          ///< The week index.
  day_of_week day{day_of_week::monday};  ///< The current day.
  cen::color tint;                       ///< Light tint.
};

/// \} End of group components

}  // namespace wanderer::comp