#pragma once

#include <entt.hpp>    // registry, entity, null
#include <functional>  // reference_wrapper

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct end_humanoid_move
 *
 * \brief Used for events dispatched when a humanoid stops moving.
 *
 * \headerfile end_humanoid_move_event.hpp
 */
struct end_humanoid_move final
{
  std::reference_wrapper<entt::registry> registry;  ///< The associated registry.
  entt::entity entity{entt::null};  ///< The entity that should stop moving.
};

}  // namespace wanderer::event
