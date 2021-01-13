#include "event_connections.hpp"

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "end_attack_event.hpp"
#include "end_humanoid_move_event.hpp"
#include "humanoid_attack_event_handler.hpp"
#include "humanoid_move_event_handler.hpp"
#include "interaction_handler_system.hpp"

namespace wanderer {

void connect_events(entt::dispatcher& dispatcher)
{
  using namespace sys;
  using namespace sys::humanoid;
  dispatcher.sink<comp::begin_attack_event>().connect<&on_attack_begin>();
  dispatcher.sink<comp::end_attack_event>().connect<&on_attack_end>();
  dispatcher.sink<comp::begin_humanoid_move_event>().connect<&on_move_begin>();
  dispatcher.sink<comp::end_humanoid_move_event>().connect<&on_move_end>();
  dispatcher.sink<comp::interact_event>().connect<&on_interact>();
}

void disconnect_events(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<comp::end_humanoid_move_event>().disconnect();
  dispatcher.sink<comp::begin_humanoid_move_event>().disconnect();
  dispatcher.sink<comp::end_attack_event>().disconnect();
  dispatcher.sink<comp::begin_attack_event>().disconnect();
  dispatcher.sink<comp::interact_event>().disconnect();
}

}  // namespace wanderer
