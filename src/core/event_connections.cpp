#include "event_connections.hpp"

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "end_attack_event.hpp"
#include "end_humanoid_move_event.hpp"
#include "humanoid_attack_event_handler.hpp"
#include "humanoid_move_event_handler.hpp"

namespace wanderer {

void connect_events(entt::dispatcher& dispatcher)
{
  using namespace sys::humanoid;
  dispatcher.sink<BeginAttackEvent>().connect<&on_attack_begin>();
  dispatcher.sink<EndAttackEvent>().connect<&on_attack_end>();
  dispatcher.sink<BeginHumanoidMoveEvent>().connect<&on_move_begin>();
  dispatcher.sink<EndHumanoidMoveEvent>().connect<&on_move_end>();
}

void disconnect_events(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<EndHumanoidMoveEvent>().disconnect();
  dispatcher.sink<BeginHumanoidMoveEvent>().disconnect();
  dispatcher.sink<EndAttackEvent>().disconnect();
  dispatcher.sink<BeginAttackEvent>().disconnect();
}

}  // namespace wanderer
