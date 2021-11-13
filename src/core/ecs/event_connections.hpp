#pragma once

#include <entt/entt.hpp>  // dispatcher

namespace wanderer {

/**
 * \brief Connects a dispatcher to all of the events used in the game.
 *
 * \param dispatcher the dispatcher that will be connected to the events.
 */
void ConnectEvents(entt::dispatcher& dispatcher);

/**
 * \brief Disconnects a dispatcher from the game events.
 *
 * \details Clears all pending events from the dispatcher and disconnects
 * all of the previously connected game events.
 *
 * \param dispatcher the dispatcher that will be cleared and disconnected
 * from events.
 */
void DisconnectEvents(entt::dispatcher& dispatcher);

}  // namespace wanderer
