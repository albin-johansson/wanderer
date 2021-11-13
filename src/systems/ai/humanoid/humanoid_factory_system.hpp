#pragma once

#include <entt/entt.hpp>  // registry, entity

#include "components/level.hpp"
#include "components/player.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

/// \name Humanoids
/// \{

/**
 * \brief Creates a player entity.
 *
 * \ingroup systems
 *
 * \param level the level that will contain the player.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created player entity.
 */
auto MakePlayer(Level& level, GraphicsContext& graphics) -> entt::entity;

/**
 * \brief Creates a skeleton entity.
 *
 * \note The player entity must be created before this function is called!
 *
 * \ingroup systems
 *
 * \param level the level that will contain the skeleton.
 * \param position the initial position of the entity.
 * \param graphics the graphics context used to load the associated textures.
 *
 * \return the created skeleton entity.
 */
auto MakeSkeleton(Level& level, Vec2 position, GraphicsContext& graphics) -> entt::entity;

/// \} End of humanoid

}  // namespace wanderer::sys
