#pragma once

#include <entt.hpp>    // registry, entity, null
#include <functional>  // reference_wrapper

#include "core/direction.hpp"

namespace wanderer {

/// \brief Used for events dispatched when a humanoid stops moving.
/// \ingroup events
struct end_humanoid_move_event final
{
  std::reference_wrapper<entt::registry> registry;  ///< The associated registry.
  entt::entity entity{entt::null};  ///< The entity that should stop moving.
};

}  // namespace wanderer
