#pragma once

#include <entt.hpp>    // registry, entity, null
#include <functional>  // reference_wrapper

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct begin_attack
 *
 * \brief Represents the data associated with the start of an attack.
 *
 * \headerfile begin_attack_event.hpp
 */
struct begin_attack final
{
  std::reference_wrapper<entt::registry> registry;  ///< The associated registry.
  entt::entity sourceEntity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};        ///< The weapon entity.
  direction dir{direction::down};         ///< The attack direction.
};

}  // namespace wanderer::event
