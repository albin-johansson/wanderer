#include "component/hitbox.hpp"

#include <catch.hpp>

#include "hitbox_system.hpp"

using namespace wanderer;

TEST_CASE("hitbox::update_bounds", "[hitbox]")
{
  /*
   * Rough visualisation of the test.
   *  _ _ _ _ _ _ _
   * |  A  |      |
   * |_____|      |
   * |       _____|
   * |      |  B  |
   * |_ _ _ |_____|
   *
   */
  comp::hitbox hitbox;

  const comp::subhitbox fst{vector2f{0, 0}, cen::frect{{10, 10}, {100, 100}}};
  const comp::subhitbox snd{
      vector2f{0, 0},
      cen::frect{{fst.rect.max_x() + 10, fst.rect.max_y() + 10}, {100, 100}}};

  hitbox.boxes.push_back(fst);
  hitbox.boxes.push_back(snd);

  sys::hitbox::update_bounds(hitbox);

  const cen::frect expected{
      {fst.rect.x(), fst.rect.y()},
      {snd.rect.max_x() - fst.rect.x(), snd.rect.max_y() - fst.rect.y()}};

  CHECK(hitbox.bounds == expected);
}

TEST_CASE("hitbox::intersects", "[hitbox]")
{
  SECTION("Valid intersection")
  {
    /*
     * Rough visualisation of the test.
     *  ___
     * |  _|__
     * |_|_| |
     *   |___|
     *
     */

    const auto fst =
        sys::hitbox::create({{{}, cen::frect{{100, 100}, {100, 100}}}});
    const auto snd =
        sys::hitbox::create({{{}, cen::frect{{150, 150}, {100, 100}}}});

    CHECK(sys::hitbox::intersects(fst, snd));
    CHECK(sys::hitbox::intersects(snd, fst));

    CHECK(cen::intersects(fst.bounds, snd.bounds));
    CHECK(cen::intersects(snd.bounds, fst.bounds));
  }

  SECTION("Bounds intersection but no actual subhitbox intersection")
  {
    /*
     * Rough visualisation of the test. The bounding rectangles look
     * something like this, but no subhitbox intersect in the hitboxes.
     *  ___
     * |  _|__
     * |_|_| |
     *   |___|
     *
     */

    const auto fst =
        sys::hitbox::create({{{}, cen::frect{{100, 100}, {75, 100}}},
                             {{}, cen::frect{{175, 100}, {25, 25}}}});

    const auto snd =
        sys::hitbox::create({{{}, cen::frect{{210, 150}, {100, 100}}},
                             {{}, cen::frect{{150, 210}, {25, 25}}}});

    REQUIRE(cen::intersects(fst.bounds, snd.bounds));
    REQUIRE(cen::intersects(snd.bounds, fst.bounds));

    CHECK(!sys::hitbox::intersects(fst, snd));
    CHECK(!sys::hitbox::intersects(snd, fst));
  }
}
