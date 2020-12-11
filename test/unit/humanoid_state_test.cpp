#include "humanoid_state.hpp"

#include <catch.hpp>

#include "add_humanoid_state_dependencies.hpp"

using namespace wanderer;

using idle = comp::humanoid_idle;
using move = comp::humanoid_move;
using attack = comp::humanoid_attack;
using die = comp::humanoid_die;

TEST_CASE("Humanoid state dependencies", "[humanoid_state]")
{
  entt::registry registry;
  add_humanoid_state_dependencies(registry);

  const auto entity = registry.create();
  registry.emplace<comp::humanoid>(entity);

  SECTION("Adding Idle component")
  {
    REQUIRE(registry.valid(entity));
    REQUIRE(!registry.has<idle>(entity));

    registry.emplace<idle>(entity);

    CHECK(registry.has<idle>(entity));
    CHECK(!registry.has<move>(entity));
    CHECK(!registry.has<attack>(entity));
    CHECK(!registry.has<die>(entity));
  }

  SECTION("Adding Move component")
  {
    REQUIRE(registry.valid(entity));
    REQUIRE(!registry.has<move>(entity));

    registry.emplace<move>(entity);

    CHECK(registry.has<move>(entity));
    CHECK(!registry.has<idle>(entity));
    CHECK(!registry.has<attack>(entity));
    CHECK(!registry.has<die>(entity));
  }

  SECTION("Adding Attack component")
  {
    REQUIRE(registry.valid(entity));
    REQUIRE(!registry.has<attack>(entity));

    registry.emplace<attack>(entity);

    CHECK(registry.has<attack>(entity));
    CHECK(!registry.has<move>(entity));
    CHECK(!registry.has<idle>(entity));
    CHECK(!registry.has<die>(entity));
  }

  SECTION("Adding Die component")
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
