#pragma once

#include <entt.hpp>  // registry, entity

#include "components/player.hpp"
#include "core/aliases/aabb_tree.hpp"
#include "core/aliases/float2.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Creates a player entity.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param tree the associated AABB tree.
 * \param position the initial position of the entity.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created player entity.
 */
auto make_player(entt::registry& registry,
                 aabb_tree& tree,
                 float2 position,
                 graphics_context& graphics) -> entt::entity;

/**
 * \brief Creates a skeleton entity.
 *
 * \note The player entity must be created before this function is called!
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param tree the associated AABB tree.
 * \param position the initial position of the entity.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created skeleton entity.
 */
auto make_skeleton(entt::registry& registry,
                   aabb_tree& tree,
                   float2 position,
                   graphics_context& graphics) -> entt::entity;

/// \} End of humanoid

}  // namespace wanderer::sys
