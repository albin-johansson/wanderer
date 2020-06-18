/**
 * This file provides the declarations of functions related to handling the
 * connections of game events to <code>entt::dispatcher</code> instances.
 *
 * @file event_connections.h
 */

#pragma once

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * Connects a dispatcher to all of the events used in the game.
 *
 * @param dispatcher the dispatcher that will be connected to the events.
 */
void connect_events(entt::dispatcher& dispatcher);

/**
 * Clears all pending events from the dispatcher and disconnects all of the
 * previously connected Wanderer events.
 *
 * @param dispatcher the dispatcher that will be cleared and disconnected
 * from events.
 */
void disconnect_events(entt::dispatcher& dispatcher);

}  // namespace wanderer
