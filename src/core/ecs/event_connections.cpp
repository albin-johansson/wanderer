#include "event_connections.hpp"

#include "events/begin_attack_event.hpp"
#include "events/begin_humanoid_move_event.hpp"
#include "events/end_attack_event.hpp"
#include "events/end_humanoid_move_event.hpp"
#include "systems/humanoid/humanoid_attack_event_handler.hpp"
#include "systems/humanoid/humanoid_move_event_handler.hpp"
#include "systems/interaction_system.hpp"

namespace wanderer {

void connect_events(entt::dispatcher& dispatcher)
{
  using namespace sys;
  dispatcher.sink<event::begin_attack>().connect<&on_attack_begin>();
  dispatcher.sink<event::end_attack>().connect<&on_attack_end>();
  dispatcher.sink<event::begin_humanoid_move>().connect<&on_move_begin>();
  dispatcher.sink<event::end_humanoid_move>().connect<&on_move_end>();
  dispatcher.sink<event::interact>().connect<&on_interact>();
}

void disconnect_events(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<event::end_humanoid_move>().disconnect();
  dispatcher.sink<event::begin_humanoid_move>().disconnect();
  dispatcher.sink<event::end_attack>().disconnect();
  dispatcher.sink<event::begin_attack>().disconnect();
  dispatcher.sink<event::interact>().disconnect();
}

}  // namespace wanderer
