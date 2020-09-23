/**
 * @brief Provides the `EndAttackEvent` component.
 * @file end_attack_event.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer {

/**
 * @struct EndAttackEvent
 * @brief Represents the data associated with the end of an attack.
 *
 * @note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 * @code{.cpp}
 * const entt::entity srcEntity = ...;
 * const entt::entity weapon = ...;
 * const auto direction = Direction::Down;
 * dispatcher.enqueue<EndAttackEvent>(&registry,
 *                                    srcEntity,
 *                                    weapon,
 *                                    direction);
 * @endcode
 *
 * @var EndAttackEvent::registry
 * A pointer to the associated registry.
 * @var EndAttackEvent::sourceEntity
 * The entity that initiated the attack.
 * @var EndAttackEvent::weapon
 * The weapon that is being used for the attack.
 * @var EndAttackEvent::direction
 * The direction in which the attack is being performed.
 *
 * @headerfile end_attack_event.hpp
 */
struct EndAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon tag type
  Direction direction{Direction::Down};

  EndAttackEvent(entt::registry* registry,
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
