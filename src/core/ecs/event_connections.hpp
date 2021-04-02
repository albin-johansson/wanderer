#pragma once

#include <entt.hpp>

namespace wanderer {

/**
 * \brief Connects a dispatcher to all of the events used in the game.
 *
 * \param dispatcher the dispatcher that will be connected to the events.
 */
void connect_events(entt::dispatcher& dispatcher);

/**
 * \brief Disconnects a dispatcher from the game events.
 *
 * \details Clears all pending events from the dispatcher and disconnects
 * all of the previously connected game events.
 *
 * \param dispatcher the dispatcher that will be cleared and disconnected
 * from events.
 */
void disconnect_events(entt::dispatcher& dispatcher);

}  // namespace wanderer
