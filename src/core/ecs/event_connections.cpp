#include "event_connections.hpp"

#include "events/humanoid_events.hpp"
#include "systems/ai/humanoid/humanoid_attack_event_handler.hpp"
#include "systems/ai/humanoid/humanoid_move_event_handler.hpp"
#include "systems/interaction_system.hpp"

namespace wanderer {

void ConnectEvents(entt::dispatcher& dispatcher)
{
  using namespace sys;
  dispatcher.sink<BeginAttackEvent>().connect<&OnAttackBegin>();
  dispatcher.sink<EndAttackEvent>().connect<&OnAttackEnd>();
  dispatcher.sink<BeginHumanoidMoveEvent>().connect<&OnMoveBegin>();
  dispatcher.sink<EndHumanoidMoveEvent>().connect<&OnMoveEnd>();
  dispatcher.sink<InteractEvent>().connect<&OnInteract>();
}

void DisconnectEvents(entt::dispatcher& dispatcher)
{
  dispatcher.clear();
  dispatcher.sink<EndHumanoidMoveEvent>().disconnect();
  dispatcher.sink<BeginHumanoidMoveEvent>().disconnect();
  dispatcher.sink<EndAttackEvent>().disconnect();
  dispatcher.sink<BeginAttackEvent>().disconnect();
  dispatcher.sink<InteractEvent>().disconnect();
}

}  // namespace wanderer
