/**
 * @brief Provides the `BeginAttackEvent` component.
 * @file begin_attack_event.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @struct BeginAttackEvent
 * @brief Represents the data associated with the start of an attack.
 *
 * @note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 * @code{.cpp}
 * const entt::entity srcEntity = ...;
 * const entt::entity weapon = ...;
 * const auto direction = Direction::Down;
 * dispatcher.enqueue<BeginAttackEvent>(&registry,
 *                                      srcEntity,
 *                                      weapon,
 *                                      direction);
 * @endcode
 *
 * @var BeginAttackEvent::registry
 * A pointer to the associated registry.
 * @var BeginAttackEvent::sourceEntity
 * The entity that initiated the attack.
 * @var BeginAttackEvent::weapon
 * The weapon that is being used for the attack.
 * @var BeginAttackEvent::direction
 * The direction in which the attack is being performed.
 *
 * @headerfile begin_attack_event.h
 */
struct BeginAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon component entity tag
  Direction direction{Direction::Down};

  BeginAttackEvent(entt::registry* registry,
                   const entt::entity sourceEntity,
                   const entt::entity weapon,
                   const Direction direction)
      : registry{registry},
        sourceEntity{sourceEntity},
        weapon{weapon},
        direction{direction}
  {}
};

}  // namespace wanderer
