#include "event_connections.hpp"

#include <gtest/gtest.h>

#include <entt.hpp>

#include "begin_attack.hpp"
#include "begin_humanoid_move.hpp"
#include "end_attack.hpp"
#include "end_humanoid_move.hpp"
#include "interact.hpp"

using namespace wanderer;

TEST(EventConnections, Correctness)
{
  entt::dispatcher dispatcher;

  {  // Connect the events
    connect_events(dispatcher);

    EXPECT_FALSE(dispatcher.sink<comp::begin_attack_event>().empty());
    EXPECT_FALSE(dispatcher.sink<comp::end_attack_event>().empty());
    EXPECT_FALSE(dispatcher.sink<comp::begin_humanoid_move_event>().empty());
    EXPECT_FALSE(dispatcher.sink<comp::end_humanoid_move_event>().empty());
    EXPECT_FALSE(dispatcher.sink<comp::interact_event>().empty());
  }

  {  // Disconnect the events
    disconnect_events(dispatcher);

    EXPECT_TRUE(dispatcher.sink<comp::begin_attack_event>().empty());
    EXPECT_TRUE(dispatcher.sink<comp::end_attack_event>().empty());
    EXPECT_TRUE(dispatcher.sink<comp::begin_humanoid_move_event>().empty());
    EXPECT_TRUE(dispatcher.sink<comp::end_humanoid_move_event>().empty());
    EXPECT_TRUE(dispatcher.sink<comp::interact_event>().empty());
  }
}
