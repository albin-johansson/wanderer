#include "event_connections.hpp"

#include "component/begin_attack_event.hpp"
#include "component/begin_humanoid_move_event.hpp"
#include "component/end_attack_event.hpp"
#include "component/end_humanoid_move_event.hpp"
#include "humanoid_attack_event_handler.hpp"
#include "humanoid_move_event_handler.hpp"

namespace wanderer {

using namespace comp;

void connect_events(entt::dispatcher& dispatcher)
{
  {
    using namespace sys::humanoid;
    dispatcher.sink<begin_attack_event>().connect<&on_attack_begin>();
    dispatcher.sink<end_attack_event>().connect<&on_attack_end>();
    dispatcher.sink<begin_humanoid_move_event>().connect<&on_move_begin>();
    dispatcher.sink<end_humanoid_move_event>().connect<&on_move_end>();
  }
}

void disconnect_events(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<end_humanoid_move_event>().disconnect();
  dispatcher.sink<begin_humanoid_move_event>().disconnect();
  dispatcher.sink<end_attack_event>().disconnect();
  dispatcher.sink<begin_attack_event>().disconnect();
}

}  // namespace wanderer
