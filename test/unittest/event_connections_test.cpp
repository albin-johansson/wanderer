#include "event_connections.h"

#include <doctest.h>

#include "begin_attack_event.h"
#include "begin_humanoid_move_event.h"
#include "end_attack_event.h"
#include "end_humanoid_move_event.h"
#include "wanderer_stdinc.h"

using namespace wanderer;

TEST_SUITE("Event connections")
{
  entt::dispatcher dispatcher;

  TEST_CASE("Connect the events")
  {
    connect_events(dispatcher);

    CHECK(!dispatcher.sink<BeginAttackEvent>().empty());
    CHECK(!dispatcher.sink<EndAttackEvent>().empty());
    CHECK(!dispatcher.sink<BeginHumanoidMoveEvent>().empty());
    CHECK(!dispatcher.sink<EndHumanoidMoveEvent>().empty());
  }

  TEST_CASE("Disconnect the events")
  {
    disconnect_events(dispatcher);

    CHECK(dispatcher.sink<BeginAttackEvent>().empty());
    CHECK(dispatcher.sink<EndAttackEvent>().empty());
    CHECK(dispatcher.sink<BeginHumanoidMoveEvent>().empty());
    CHECK(dispatcher.sink<EndHumanoidMoveEvent>().empty());
  }
}
