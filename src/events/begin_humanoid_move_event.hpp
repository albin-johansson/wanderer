#pragma once

#include <entt.hpp>  // registry, entity

#include "common/ref.hpp"
#include "core/direction.hpp"

namespace wanderer {

/// \brief Used for events dispatched when a humanoid starts to move.
/// \ingroup events
struct begin_humanoid_move_event final
{
  ref<entt::registry> registry;     ///< The associated registry.
  entt::entity entity{entt::null};  ///< Humanoid that should start moving.
  direction dir{direction::down};   ///< Movement direction.
};

}  // namespace wanderer
