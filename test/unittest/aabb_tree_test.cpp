#include "aabb_tree.hpp"

#include <catch.hpp>
#include <entt.hpp>
#include <iterator>  // back_inserter
#include <vector>    // vector

using namespace wanderer;

TEST_CASE("aabb_tree::insert", "[aabb_tree]")
{
  entt::registry registry;
  aabb_tree tree;

  CHECK(tree.empty());

  const auto e1 = registry.create();
  const auto e2 = registry.create();
  const auto e3 = registry.create();

  tree.insert(e1, make_aabb({0, 0}, {100, 100}));
  CHECK(!tree.empty());
  CHECK(tree.size() == 1);

  tree.insert(e2, make_aabb({40, 40}, {100, 100}));
  CHECK(tree.size() == 2);

  tree.insert(e3, make_aabb({75, 75}, {100, 100}));
  CHECK(tree.size() == 3);
}

TEST_CASE("aabb_tree::update", "[aabb_tree]")
{
  entt::registry registry;
  aabb_tree tree;

  CHECK(tree.empty());

  const auto entity = registry.create();

  const auto original = make_aabb({0, 0}, {100, 100});
  tree.insert(entity, original);

  SECTION("Update to smaller AABB")
  {
    // When the new AABB is smaller, nothing is done
    const auto smaller = make_aabb({10, 10}, {50, 50});
    tree.update(entity, smaller);

    const auto& actual = tree.get_aabb(entity);
    CHECK(original.min == actual.min);
    CHECK(original.max == actual.max);
    CHECK(original.area == actual.area);
  }

  SECTION("Update to larger AABB")
  {
    const auto larger = make_aabb({20, 20}, {150, 150});
    tree.update(entity, larger);

    const auto& actual = tree.get_aabb(entity);
    CHECK(larger.min == actual.min);
    CHECK(larger.max == actual.max);
    CHECK(larger.area == actual.area);
  }
}

TEST_CASE("aabb_tree::remove", "[aabb_tree]")
{
  entt::registry registry;
  aabb_tree tree;

  const auto e1 = registry.create();
  const auto e2 = registry.create();
  const auto box1 = make_aabb({0, 0}, {100, 100});
  const auto box2 = make_aabb({50, 35}, {200, 250});

  tree.insert(e1, box1);
  tree.insert(e2, box2);
  CHECK(tree.size() == 2);

  tree.remove(e1);
  CHECK(tree.size() == 1);

  tree.remove(e2);
  CHECK(tree.empty());
}