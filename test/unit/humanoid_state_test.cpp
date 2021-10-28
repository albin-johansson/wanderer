#include <gtest/gtest.h>

#include "components/humanoid.hpp"
#include "core/ecs/add_humanoid_state_dependencies.hpp"

using namespace wanderer;

using Idle = comp::HumanoidIdle;
using Move = comp::HumanoidMove;
using Attack = comp::HumanoidAttack;
using Die = comp::HumanoidDie;

TEST(HumanoidState, Dependencies)
{
  entt::registry registry;
  AddHumanoidStateDependencies(registry);

  const auto entity = registry.create();
  registry.emplace<comp::Humanoid>(entity);

  {  // Idle
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<Idle>(entity));

    registry.emplace<Idle>(entity);
    EXPECT_TRUE(registry.all_of<Idle>(entity));
    EXPECT_FALSE(registry.all_of<Move>(entity));
    EXPECT_FALSE(registry.all_of<Attack>(entity));
    EXPECT_FALSE(registry.all_of<Die>(entity));
  }

  {  // Move
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<Move>(entity));

    registry.emplace<Move>(entity);
    EXPECT_TRUE(registry.all_of<Move>(entity));
    EXPECT_FALSE(registry.all_of<Idle>(entity));
    EXPECT_FALSE(registry.all_of<Attack>(entity));
    EXPECT_FALSE(registry.all_of<Die>(entity));
  }

  {  // Attack
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<Attack>(entity));

    registry.emplace<Attack>(entity);
    EXPECT_TRUE(registry.all_of<Attack>(entity));
    EXPECT_FALSE(registry.all_of<Move>(entity));
    EXPECT_FALSE(registry.all_of<Idle>(entity));
    EXPECT_FALSE(registry.all_of<Die>(entity));
  }

  {  // Die
    ASSERT_TRUE(registry.valid(entity));
    ASSERT_FALSE(registry.all_of<Die>(entity));

    registry.emplace<Die>(entity);
    EXPECT_TRUE(registry.all_of<Die>(entity));
    EXPECT_FALSE(registry.all_of<Attack>(entity));
    EXPECT_FALSE(registry.all_of<Move>(entity));
    EXPECT_FALSE(registry.all_of<Idle>(entity));
  }
}
