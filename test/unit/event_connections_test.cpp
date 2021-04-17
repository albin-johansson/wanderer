#include "core/ecs/event_connections.hpp"

#include <gtest/gtest.h>

#include <entt.hpp>

#include "events/begin_attack_event.hpp"
#include "events/begin_humanoid_move_event.hpp"
#include "events/end_attack_event.hpp"
#include "events/end_humanoid_move_event.hpp"
#include "events/interact_event.hpp"

using namespace wanderer;

TEST(EventConnections, Correctness)
{
  entt::dispatcher dispatcher;

  {  // Connect the events
    connect_events(dispatcher);

    EXPECT_FALSE(dispatcher.sink<begin_attack_event>().empty());
    EXPECT_FALSE(dispatcher.sink<end_attack_event>().empty());
    EXPECT_FALSE(dispatcher.sink<begin_humanoid_move_event>().empty());
    EXPECT_FALSE(dispatcher.sink<end_humanoid_move_event>().empty());
    EXPECT_FALSE(dispatcher.sink<interact_event>().empty());
  }

  {  // Disconnect the events
    disconnect_events(dispatcher);

    EXPECT_TRUE(dispatcher.sink<begin_attack_event>().empty());
    EXPECT_TRUE(dispatcher.sink<end_attack_event>().empty());
    EXPECT_TRUE(dispatcher.sink<begin_humanoid_move_event>().empty());
    EXPECT_TRUE(dispatcher.sink<end_humanoid_move_event>().empty());
    EXPECT_TRUE(dispatcher.sink<interact_event>().empty());
  }
}
