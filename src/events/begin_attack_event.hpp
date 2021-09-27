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

}  // namespace wanderer
