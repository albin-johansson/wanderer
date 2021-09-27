#pragma once

#include <entt.hpp>  // registry, dispatcher, entity, null

#include "common/ref.hpp"
#include "core/direction.hpp"

namespace wanderer {

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

}  // namespace wanderer
