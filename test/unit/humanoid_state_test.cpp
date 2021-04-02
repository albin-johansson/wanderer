#include "humanoid_state.hpp"

#include <gtest/gtest.h>

#include "add_humanoid_state_dependencies.hpp"

using namespace wanderer;

using idle = comp::humanoid_idle;
using move = comp::humanoid_move;
using attack = comp::humanoid_attack;
using die = comp::humanoid_die;

TEST(HumanoidState, Dependencies)
{
  entt::registry registry;
  add_humanoid_state_dependencies(registry);

  const auto entity = registry.create();
  registry.emplace<comp::humanoid>(entity);

  {  // Idle
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.has<idle>(entity));

    registry.emplace<idle>(entity);
    EXPECT_TRUE(registry.has<idle>(entity));
    EXPECT_FALSE(registry.has<move>(entity));
    EXPECT_FALSE(registry.has<attack>(entity));
    EXPECT_FALSE(registry.has<die>(entity));
  }

  {  // Move
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.has<move>(entity));

    registry.emplace<move>(entity);
    EXPECT_TRUE(registry.has<move>(entity));
    EXPECT_FALSE(registry.has<idle>(entity));
    EXPECT_FALSE(registry.has<attack>(entity));
    EXPECT_FALSE(registry.has<die>(entity));
  }

  {  // Attack
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.has<attack>(entity));

    registry.emplace<attack>(entity);
    EXPECT_TRUE(registry.has<attack>(entity));
    EXPECT_FALSE(registry.has<move>(entity));
    EXPECT_FALSE(registry.has<idle>(entity));
    EXPECT_FALSE(registry.has<die>(entity));
  }

  {  // Die
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.has<die>(entity));

    registry.emplace<die>(entity);
    EXPECT_TRUE(registry.has<die>(entity));
    EXPECT_FALSE(registry.has<attack>(entity));
    EXPECT_FALSE(registry.has<move>(entity));
    EXPECT_FALSE(registry.has<idle>(entity));
  }
}
