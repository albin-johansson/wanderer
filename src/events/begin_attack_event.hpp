#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct begin_attack
 *
 * \brief Represents the data associated with the start of an attack.
 *
 * \note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 *
 * \var begin_attack_event::registry
 * A pointer to the associated registry.
 * \var begin_attack_event::sourceEntity
 * The entity that initiated the attack.
 * \var begin_attack_event::weapon
 * The weapon that is being used for the attack.
 * \var begin_attack_event::direction
 * The direction in which the attack is being performed.
 *
 * \headerfile begin_attack_event.hpp
 */
struct begin_attack final
{
  entt::registry* registry{};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon component entity tag
  direction dir{direction::down};
};

}  // namespace wanderer::event
