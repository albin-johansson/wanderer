#pragma once

#include <box2d/box2d.h>
#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/data/day.hpp"
#include "wanderer/data/mob.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief Component featured by all physical objects in the game world.
 */
struct GameObject final
{
  glm::vec2 position{};  ///< The position in logical coordinates.
  glm::vec2 size{};      ///< The size of the object.
};

/**
 * \brief Component featured by all entities that are a part of the physics simulation.
 */
struct PhysicsBody final
{
  b2Body* data{};       ///< The simulation body data.
  b2Vec2 offset{};      ///< Body offset from the game object origin, in simulation scale.
  b2Vec2 size{};        ///< The size of the body, in simulation scale.
  float32 max_speed{};  ///< Maximum total speed, in simulation scale.
};

/**
 * \brief Context component representing the physics simulation.
 */
struct PhysicsWorld final
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
struct DateAndTime final
{
  float32 hour{};                    ///< [0, 24)
  float32 minute{};                  ///< [0, 60)
  float32 seconds{};                 ///< Reset once per in-game day.
  int32 week{};                      ///< The week index.
  DayOfWeek day{DayOfWeek::monday};  ///< The current day.
  cen::color tint;                   ///< Light tint.
};

/**
 * \brief Represents a possible spawn point for a mob type in the world.
 */
struct SpawnPoint final
{
  MobType mob{};  ///< The mob type that should be spawned.
};

/// \} End of group components

}  // namespace wanderer::comp