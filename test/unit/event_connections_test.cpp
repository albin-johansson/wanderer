#include "event_connections.hpp"

#include <gtest/gtest.h>

#include <entt.hpp>

#include "begin_attack_event.hpp"
#include "begin_humanoid_move_event.hpp"
#include "end_attack_event.hpp"
#include "end_humanoid_move_event.hpp"
#include "interact_event.hpp"

using namespace wanderer;

TEST(EventConnections, Correctness)
{
  entt::dispatcher dispatcher;

  {  // Connect the events
    connect_events(dispatcher);

    EXPECT_FALSE(dispatcher.sink<event::begin_attack>().empty());
    EXPECT_FALSE(dispatcher.sink<event::end_attack>().empty());
    EXPECT_FALSE(dispatcher.sink<event::begin_humanoid_move>().empty());
    EXPECT_FALSE(dispatcher.sink<event::end_humanoid_move>().empty());
    EXPECT_FALSE(dispatcher.sink<event::interact>().empty());
  }

  {  // Disconnect the events
    disconnect_events(dispatcher);

    EXPECT_TRUE(dispatcher.sink<event::begin_attack>().empty());
    EXPECT_TRUE(dispatcher.sink<event::end_attack>().empty());
    EXPECT_TRUE(dispatcher.sink<event::begin_humanoid_move>().empty());
    EXPECT_TRUE(dispatcher.sink<event::end_humanoid_move>().empty());
    EXPECT_TRUE(dispatcher.sink<event::interact>().empty());
  }
}
