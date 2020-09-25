#include "aabb_tree.hpp"

#include <catch.hpp>
#include <entt.hpp>
#include <log.hpp>

using namespace wanderer::experimental;

TEST_CASE("aabb_tree::insert_object", "[aabb_tree]")
{
  entt::registry registry;
  aabb_tree tree;

  const auto e1 = registry.create();
  const auto e2 = registry.create();

  tree.insert_object(e1, make_aabb({0, 0}, {100, 100}));
  tree.insert_object(e2, make_aabb({40, 40}, {100, 100}));

  const auto candidates = tree.query_overlaps(e1);
  for (const auto entity : candidates) {
    cen::log::info("Found collision candidate: %i", static_cast<int>(entity));
  }
  //  tree.update_object(id, {{10, 10}, {100, 100}});
  //  tree.remove_object(id);

  //
  //  CHECK(tree.size() == 1);
}