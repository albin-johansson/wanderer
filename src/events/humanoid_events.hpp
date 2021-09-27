#pragma once

#include <entt.hpp>  // registry, entity, null

#include "common/ref.hpp"
#include "core/direction.hpp"

namespace wanderer {

/// \brief Represents the data associated with the start of an attack.
/// \ingroup events
struct begin_attack_event final
{
  ref<entt::registry> registry;            ///< The associated registry.
  entt::entity source_entity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};         ///< The weapon entity.
  direction dir{direction::down};          ///< The attack direction.
};

/// \brief Represents the data associated with the end of an attack.
/// \ingroup events
struct end_attack_event final
{
  ref<entt::registry> registry;            ///< The associated registry.
  ref<entt::dispatcher> dispatcher;        ///< The common dispatcher.
  entt::entity source_entity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};         ///< The weapon entity.
  direction dir{direction::down};          ///< The attack direction.
};

/// \brief Used for events dispatched when a humanoid starts to move.
/// \ingroup events
struct begin_humanoid_move_event final
{
  ref<entt::registry> registry;     ///< The associated registry.
  entt::entity entity{entt::null};  ///< Humanoid that should start moving.
  direction dir{direction::down};   ///< Movement direction.
};

/// \brief Used for events dispatched when a humanoid stops moving.
/// \ingroup events
struct end_humanoid_move_event final
{
  ref<entt::registry> registry;     ///< The associated registry.
  entt::entity entity{entt::null};  ///< The entity that should stop moving.
};

}  // namespace wanderer
