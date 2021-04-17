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
  dispatcher.sink<begin_attack_event>().connect<&on_attack_begin>();
  dispatcher.sink<end_attack_event>().connect<&on_attack_end>();
  dispatcher.sink<begin_humanoid_move_event>().connect<&on_move_begin>();
  dispatcher.sink<end_humanoid_move_event>().connect<&on_move_end>();
  dispatcher.sink<interact_event>().connect<&on_interact>();
}

void disconnect_events(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<end_humanoid_move_event>().disconnect();
  dispatcher.sink<begin_humanoid_move_event>().disconnect();
  dispatcher.sink<end_attack_event>().disconnect();
  dispatcher.sink<begin_attack_event>().disconnect();
  dispatcher.sink<interact_event>().disconnect();
}

}  // namespace wanderer
