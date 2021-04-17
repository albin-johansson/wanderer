#pragma once

#include <entt.hpp>    // registry, entity
#include <functional>  // reference_wrapper

#include "core/direction.hpp"

namespace wanderer {

/**
 * \struct begin_humanoid_move_event
 *
 * \brief Used for events dispatched when a humanoid starts to move.
 *
 * \headerfile begin_humanoid_move_event.hpp
 */
struct begin_humanoid_move_event final
{
  std::reference_wrapper<entt::registry> registry;  ///< The associated registry.
  entt::entity entity{entt::null};  ///< Humanoid that should start moving.
  direction dir{direction::down};   ///< Movement direction.
};

}  // namespace wanderer
