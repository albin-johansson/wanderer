#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer {

/**
 * @struct end_attack_event
 *
 * @brief Represents the data associated with the end of an attack.
 *
 * @note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 *
 * @var end_attack_event::registry
 * A pointer to the associated registry.
 * @var end_attack_event::sourceEntity
 * The entity that initiated the attack.
 * @var end_attack_event::weapon
 * The weapon that is being used for the attack.
 * @var end_attack_event::direction
 * The direction in which the attack is being performed.
 *
 * @headerfile end_attack_event.hpp
 */
struct end_attack_event final
{
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon tag type
  direction direction{direction::down};
};

}  // namespace wanderer
