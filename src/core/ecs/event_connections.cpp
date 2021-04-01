#include "event_connections.hpp"

#include "begin_attack.hpp"
#include "begin_humanoid_move.hpp"
#include "end_attack.hpp"
#include "end_humanoid_move.hpp"
#include "humanoid_attack_event_handler.hpp"
#include "humanoid_move_event_handler.hpp"
#include "interaction_handler_system.hpp"

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
