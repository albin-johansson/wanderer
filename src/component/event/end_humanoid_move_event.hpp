/**
 * @brief Provides the `EndHumanoidMoveEvent` component.
 * @file end_humanoid_move_event.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer {

/**
 * @struct EndHumanoidMoveEvent
 * @brief Used for events dispatched when a humanoid stops moving.
 *
 * @note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 * @code{.cpp}
 * dispatcher.enqueue<EndHumanoidMoveEvent>(&registry, entity);
 * @endcode
 *
 * @var EndHumanoidMoveEvent::registry
 * A pointer to the associated registry.
 * @var EndHumanoidMoveEvent::entity
 * The humanoid that should stop moving.
 *
 * @headerfile end_humanoid_move_event.hpp
 */
struct EndHumanoidMoveEvent final
{
  entt::registry* registry{nullptr};
  entt::entity entity{entt::null};  // TODO tag type

  EndHumanoidMoveEvent(entt::registry* registry,
                       const entt::entity entity) noexcept
      : registry{registry},
        entity{entity}
  {}
};

}  // namespace wanderer
