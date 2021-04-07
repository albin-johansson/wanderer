#pragma once

#include <entt.hpp>    // registry, entity
#include <functional>  // reference_wrapper

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct begin_humanoid_move
 *
 * \brief Used for events dispatched when a humanoid starts to move.
 *
 * \headerfile begin_humanoid_move_event.hpp
 */
struct begin_humanoid_move final
{
  std::reference_wrapper<entt::registry> registry;  ///< The associated registry.
  entt::entity entity{entt::null};  ///< Humanoid that should start moving.
  direction dir{direction::down};   ///< Movement direction.
};

}  // namespace wanderer::event
