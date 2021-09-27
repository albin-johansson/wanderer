#include "components/ai/humanoid_state.hpp"

#include <gtest/gtest.h>

#include "core/ecs/add_humanoid_state_dependencies.hpp"

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
    ASSERT_FALSE(registry.all_of<idle>(entity));

    registry.emplace<idle>(entity);
    EXPECT_TRUE(registry.all_of<idle>(entity));
    EXPECT_FALSE(registry.all_of<move>(entity));
    EXPECT_FALSE(registry.all_of<attack>(entity));
    EXPECT_FALSE(registry.all_of<die>(entity));
  }

  {  // Move
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<move>(entity));

    registry.emplace<move>(entity);
    EXPECT_TRUE(registry.all_of<move>(entity));
    EXPECT_FALSE(registry.all_of<idle>(entity));
    EXPECT_FALSE(registry.all_of<attack>(entity));
    EXPECT_FALSE(registry.all_of<die>(entity));
  }

  {  // Attack
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<attack>(entity));

    registry.emplace<attack>(entity);
    EXPECT_TRUE(registry.all_of<attack>(entity));
    EXPECT_FALSE(registry.all_of<move>(entity));
    EXPECT_FALSE(registry.all_of<idle>(entity));
    EXPECT_FALSE(registry.all_of<die>(entity));
  }

  {  // Die
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<die>(entity));

    registry.emplace<die>(entity);
    EXPECT_TRUE(registry.all_of<die>(entity));
    EXPECT_FALSE(registry.all_of<attack>(entity));
    EXPECT_FALSE(registry.all_of<move>(entity));
    EXPECT_FALSE(registry.all_of<idle>(entity));
  }
}
