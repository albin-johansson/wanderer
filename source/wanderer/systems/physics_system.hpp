#pragma once

#include <box2d/box2d.h>
#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup physics-system Physics system
 *
 * \brief Manages physics related aspects of the game.
 */

/// \addtogroup physics-system
/// \{

/**
 * \brief Makes an entity a part of the physics simulation.
 *
 * \details The entity will have a `comp::physics_body` component added to it.
 *
 * \param registry the level registry.
 * \param entity the target entity.
 * \param type the body type.
 * \param logicalPos the position of the game object, in logical space.
 * \param logicalSize the size of the game object, in logical space.
 * \param maxSpeed the maximum total speed of the object.
 */
void add_physics_body(entt::registry& registry,
                      entt::entity entity,
                      b2BodyType type,
                      const glm::vec2& logicalPos,
                      const glm::vec2& logicalSize,
                      float32 maxSpeed);

/**
 * \brief Destroys the simulation data associated with a physics object.
 *
 * \details This function is meant to be called for each time an entity featuring a
 * `physics_object` component is destroyed.
 *
 * \note The `b2World` class automatically frees all created bodies and fixtures upon
 * destruction, so this is just used for simulated entities that are destroyed
 * "in-flight".
 *
 * \param registry the level registry.
 * \param entity the entity that will be destroyed.
 */
void on_destroy_physics_object(entt::registry& registry, entt::entity entity);

/**
 * \brief Updates the physics simulation.
 *
 * \param registry the level registry.
 * \param dt the current delta time.
 */
void update_physics(entt::registry& registry, float32 dt);

/**
 * \brief Debug the physics simulation by rendering collision shapes.
 *
 * \param registry the level registry.
 * \param graphics the current graphics context.
 */
void debug_physics(const entt::registry& registry, graphics_ctx& graphics);

/**
 * \brief Converts a vector in logical coordinates to simulation coordinates.
 *
 * \param registry the level registry.
 * \param vec the logical vector.
 *
 * \return a corresponding vector in simulation coordinates.
 */
[[nodiscard]] auto to_physics_world(const entt::registry& registry, const glm::vec2& vec)
    -> b2Vec2;

/**
 * \brief Converts a vector in simulation coordinates to logical coordinates.
 *
 * \param registry the level registry.
 * \param vec the simulation vector.
 *
 * \return a corresponding vector in logical coordinates.
 */
[[nodiscard]] auto to_logical_world(const entt::registry& registry, const b2Vec2& vec)
    -> glm::vec2;

/// \} End of group physics-system

}  // namespace wanderer::sys