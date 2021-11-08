#pragma once

#include <entt.hpp>  // registry, entity, null

#include "core/direction.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Represents the data associated with the start of an attack.
/// \ingroup events
struct BeginAttackEvent final
{
  Ref<entt::registry> registry;            ///< The associated registry.
  entt::entity source_entity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};         ///< The weapon entity.
  Direction dir{Direction::Down};          ///< The attack Direction.
};

/// \brief Represents the data associated with the end of an attack.
/// \ingroup events
struct EndAttackEvent final
{
  Ref<entt::registry> registry;            ///< The associated registry.
  Ref<entt::dispatcher> dispatcher;        ///< The common dispatcher.
  entt::entity source_entity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};         ///< The weapon entity.
  Direction dir{Direction::Down};          ///< The attack Direction.
};

/// \brief Used for events dispatched when a humanoid starts to move.
/// \ingroup events
struct BeginHumanoidMoveEvent final
{
  Ref<entt::registry> registry;     ///< The associated registry.
  entt::entity entity{entt::null};  ///< Humanoid that should start moving.
  Direction dir{Direction::Down};   ///< Movement Direction.
};

/// \brief Used for events dispatched when a humanoid stops moving.
/// \ingroup events
struct EndHumanoidMoveEvent final
{
  Ref<entt::registry> registry;     ///< The associated registry.
  entt::entity entity{entt::null};  ///< The entity that should stop moving.
};

}  // namespace wanderer
