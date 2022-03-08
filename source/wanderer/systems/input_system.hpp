#pragma once

#include <centurion.hpp>
#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup input-system Input system
 *
 * \brief Responsible for responding to user input.
 */

/// \addtogroup input-system
/// \{

/**
 * \brief Processes the current input state and dispatches appropriate events.
 *
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 */
void update_input(entt::dispatcher& dispatcher, const InputState& input);

void on_move_player(entt::registry& registry, const move_player_event& event);

void on_stop_player(entt::registry& registry, const stop_player_event& event);

/// \} End of group input-system

}  // namespace wanderer::sys
