#include "humanoid_state.h"

#include <doctest.h>

#include "add_humanoid_state_dependencies.h"

using namespace wanderer;

TEST_SUITE("Humanoid states")
{
  using Idle = HumanoidIdle;
  using Move = HumanoidMove;
  using Attack = HumanoidAttack;
  using Die = HumanoidDie;

  TEST_CASE("Humanoid state dependencies")
  {
    entt::registry registry;
    add_humanoid_state_dependencies(registry);

    const auto entity = registry.create();
    registry.emplace<Humanoid>(entity);

    SUBCASE("Adding Idle component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<Idle>(entity));

      registry.emplace<Idle>(entity);

      CHECK(registry.has<Idle>(entity));
      CHECK(!registry.has<Move>(entity));
      CHECK(!registry.has<Attack>(entity));
      CHECK(!registry.has<Die>(entity));
    }

    SUBCASE("Adding Move component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<Move>(entity));

      registry.emplace<Move>(entity);

      CHECK(registry.has<Move>(entity));
      CHECK(!registry.has<Idle>(entity));
      CHECK(!registry.has<Attack>(entity));
      CHECK(!registry.has<Die>(entity));
    }

    SUBCASE("Adding Attack component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<Attack>(entity));

      registry.emplace<Attack>(entity);

      CHECK(registry.has<Attack>(entity));
      CHECK(!registry.has<Move>(entity));
      CHECK(!registry.has<Idle>(entity));
      CHECK(!registry.has<Die>(entity));
    }

    SUBCASE("Adding Die component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<Die>(entity));

      registry.emplace<Die>(entity);

      CHECK(registry.has<Die>(entity));
      CHECK(!registry.has<Attack>(entity));
      CHECK(!registry.has<Move>(entity));
      CHECK(!registry.has<Idle>(entity));
    }
  }
}
