#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct end_attack_event
 *
 * \brief Represents the data associated with the end of an attack.
 *
 * \note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 *
 * \var end_attack::registry
 * A pointer to the associated registry.
 *
 * \var end_attack::sourceEntity
 * The entity that initiated the attack.
 *
 * \var end_attack::weapon
 * The weapon that is being used for the attack.
 *
 * \var end_attack::direction
 * The direction in which the attack is being performed.
 *
 * \headerfile end_attack_event.hpp
 */
struct end_attack final
{
  entt::registry* registry{};
  entt::dispatcher* dispatcher{};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon tag type
  direction dir{direction::down};
};

}  // namespace wanderer::event
