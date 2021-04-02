#pragma once

#include <entt.hpp>

#include "direction.hpp"

namespace wanderer::event {

/**
 * \struct begin_humanoid_move
 *
 * \brief Used for events dispatched when a humanoid starts to move.
 *
 * \note This is an event component and is meant to be dispatched through
 * `entt::dispatcher::enqueue`.
 *
 * \var begin_humanoid_move::registry
 * A pointer to the associated registry.
 *
 * \var begin_humanoid_move::entity
 * The humanoid that should start moving.
 *
 * \var begin_humanoid_move::direction
 * The direction in which the humanoid should move in.
 *
 * \headerfile begin_humanoid_move_event.hpp
 */
struct begin_humanoid_move final
{
  entt::registry* registry{};
  entt::entity entity{entt::null};  // TODO tag type
  direction dir{direction::down};
};

}  // namespace wanderer::event
