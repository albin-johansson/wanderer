#pragma once

#include <entt.hpp>    // registry, dispatcher, entity, null
#include <functional>  // reference_wrapper

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct end_attack_event
 *
 * \brief Represents the data associated with the end of an attack.
 *
 * \headerfile end_attack_event.hpp
 */
struct end_attack final
{
  std::reference_wrapper<entt::registry> registry;      ///< The associated registry.
  std::reference_wrapper<entt::dispatcher> dispatcher;  ///< The common dispatcher.
  entt::entity sourceEntity{entt::null};  ///< The entity that initiated the attack.
  entt::entity weapon{entt::null};        ///< The weapon entity.
  direction dir{direction::down};         ///< The attack direction.
};

}  // namespace wanderer::event
