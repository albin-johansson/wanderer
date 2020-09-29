#include "event_connections.hpp"

#include <catch.hpp>
#include <entt.hpp>

#include "component/begin_attack_event.hpp"
#include "component/begin_humanoid_move_event.hpp"
#include "component/end_attack_event.hpp"
#include "component/end_humanoid_move_event.hpp"

using namespace wanderer;

TEST_CASE("Event connections", "[event_connections]")
{
  entt::dispatcher dispatcher;

  SECTION("Connect the events")
  {
    connect_events(dispatcher);

    CHECK(!dispatcher.sink<comp::begin_attack_event>().empty());
    CHECK(!dispatcher.sink<comp::end_attack_event>().empty());
    CHECK(!dispatcher.sink<comp::begin_humanoid_move_event>().empty());
    CHECK(!dispatcher.sink<comp::end_humanoid_move_event>().empty());
  }

  SECTION("Disconnect the events")
  {
    disconnect_events(dispatcher);

    CHECK(dispatcher.sink<comp::begin_attack_event>().empty());
    CHECK(dispatcher.sink<comp::end_attack_event>().empty());
    CHECK(dispatcher.sink<comp::begin_humanoid_move_event>().empty());
    CHECK(dispatcher.sink<comp::end_humanoid_move_event>().empty());
  }
}
