#include "humanoid_state.h"

#include <doctest.h>

#include "add_humanoid_state_dependencies.h"

using namespace wanderer;

TEST_SUITE("Humanoid states")
{
  using idle = comp::HumanoidIdle;
  using move = comp::HumanoidMove;
  using attack = comp::HumanoidAttack;
  using die = comp::HumanoidDie;

  TEST_CASE("Humanoid state dependencies")
  {
    entt::registry registry;
    add_humanoid_state_dependencies(registry);

    const auto entity = registry.create();
    registry.emplace<comp::Humanoid>(entity);

    SUBCASE("Adding Idle component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<idle>(entity));

      registry.emplace<idle>(entity);

      CHECK(registry.has<idle>(entity));
      CHECK(!registry.has<move>(entity));
      CHECK(!registry.has<attack>(entity));
      CHECK(!registry.has<die>(entity));
    }

    SUBCASE("Adding Move component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<move>(entity));

      registry.emplace<move>(entity);

      CHECK(registry.has<move>(entity));
      CHECK(!registry.has<idle>(entity));
      CHECK(!registry.has<attack>(entity));
      CHECK(!registry.has<die>(entity));
    }

    SUBCASE("Adding Attack component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<attack>(entity));

      registry.emplace<attack>(entity);

      CHECK(registry.has<attack>(entity));
      CHECK(!registry.has<move>(entity));
      CHECK(!registry.has<idle>(entity));
      CHECK(!registry.has<die>(entity));
    }

    SUBCASE("Adding Die component")
    {
      REQUIRE(registry.valid(entity));
      REQUIRE(!registry.has<die>(entity));

      registry.emplace<die>(entity);

      CHECK(registry.has<die>(entity));
      CHECK(!registry.has<attack>(entity));
      CHECK(!registry.has<move>(entity));
      CHECK(!registry.has<idle>(entity));
    }
  }
}
