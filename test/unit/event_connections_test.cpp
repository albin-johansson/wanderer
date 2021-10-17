#include "core/ecs/event_connections.hpp"

#include <gtest/gtest.h>

#include <entt.hpp>

#include "events/humanoid_events.hpp"
#include "events/interact_event.hpp"

using namespace wanderer;

TEST(EventConnections, Correctness)
{
  entt::dispatcher dispatcher;

  {  // Connect the events
    ConnectEvents(dispatcher);

    EXPECT_FALSE(dispatcher.sink<BeginAttackEvent>().empty());
    EXPECT_FALSE(dispatcher.sink<EndAttackEvent>().empty());
    EXPECT_FALSE(dispatcher.sink<BeginHumanoidMoveEvent>().empty());
    EXPECT_FALSE(dispatcher.sink<EndHumanoidMoveEvent>().empty());
    EXPECT_FALSE(dispatcher.sink<InteractEvent>().empty());
  }

  {  // Disconnect the events
    DisconnectEvents(dispatcher);

    EXPECT_TRUE(dispatcher.sink<BeginAttackEvent>().empty());
    EXPECT_TRUE(dispatcher.sink<EndAttackEvent>().empty());
    EXPECT_TRUE(dispatcher.sink<BeginHumanoidMoveEvent>().empty());
    EXPECT_TRUE(dispatcher.sink<EndHumanoidMoveEvent>().empty());
    EXPECT_TRUE(dispatcher.sink<InteractEvent>().empty());
  }
}
