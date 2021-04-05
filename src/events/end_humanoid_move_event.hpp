#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct end_humanoid_move
 *
 * \brief Used for events dispatched when a humanoid stops moving.
 *
 * \note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 *
 * \var end_humanoid_move::registry
 * A pointer to the associated registry.
 *
 * \var end_humanoid_move::entity
 * The humanoid that should stop moving.
 *
 * \headerfile end_humanoid_move_event.hpp
 */
struct end_humanoid_move final
{
  entt::registry* registry{};
  entt::entity entity{entt::null};
};

}  // namespace wanderer::event
