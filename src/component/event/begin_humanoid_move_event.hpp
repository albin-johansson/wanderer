/**
 * @brief Provides the `BeginHumanoidMoveEvent` component.
 * @file begin_humanoid_move_event.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @struct BeginHumanoidMoveEvent
 * @brief Used for events dispatched when a humanoid starts to move.
 *
 * @note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 * @code{.cpp}
 * const entt::entity entity = ...;
 * const auto direction = Direction::Right;
 * dispatcher.enqueue<BeginHumanoidMoveEvent>(&registry, entity, direction);
 * @endcode
 *
 * @var BeginHumanoidMoveEvent::registry
 * A pointer to the associated registry.
 * @var BeginHumanoidMoveEvent::entity
 * The humanoid that should start moving.
 * @var BeginHumanoidMoveEvent::direction
 * The direction in which the humanoid should move in.
 *
 * @headerfile begin_humanoid_move_event.h
 */
struct BeginHumanoidMoveEvent final {
  entt::registry* registry{nullptr};
  entt::entity entity{entt::null};  // TODO tag type
  Direction direction{Direction::Down};

  BeginHumanoidMoveEvent(entt::registry* registry,
                         const entt::entity entity,
                         const Direction direction) noexcept
      : registry{registry}, entity{entity}, direction{direction}
  {}
};

}  // namespace wanderer
