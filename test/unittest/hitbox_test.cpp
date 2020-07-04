#include "hitbox.h"

#include <doctest.h>

#include "hitbox_system.h"

using namespace wanderer;
using namespace sys;
using namespace centurion;

using comp::Hitbox;
using comp::Subhitbox;

TEST_SUITE("Hitbox")
{
  TEST_CASE("hitbox::update_bounds | Bounds test with two rectangles")
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
    Hitbox hitbox;

    const Subhitbox fst{vector2f{0, 0}, FRect{{10, 10}, {100, 100}}};
    const Subhitbox snd{
        vector2f{0, 0},
        FRect{{fst.rect.max_x() + 10, fst.rect.max_y() + 10}, {100, 100}}};

    hitbox.boxes.push_back(fst);
    hitbox.boxes.push_back(snd);

    hitbox::update_bounds(hitbox);

    const FRect expected{
        {fst.rect.x(), fst.rect.y()},
        {snd.rect.max_x() - fst.rect.x(), snd.rect.max_y() - fst.rect.y()}};

    CHECK(hitbox.bounds == expected);
  }

  TEST_CASE("hitbox::intersects")
  {
    SUBCASE("Valid intersection")
    {
      /*
       * Rough visualisation of the test.
       *  ___
       * |  _|__
       * |_|_| |
       *   |___|
       *
       */

      const auto fst = hitbox::create({{{}, FRect{{100, 100}, {100, 100}}}});
      const auto snd = hitbox::create({{{}, FRect{{150, 150}, {100, 100}}}});

      CHECK(hitbox::intersects(fst, snd));
      CHECK(hitbox::intersects(snd, fst));

      CHECK(fst.bounds.intersects(snd.bounds));
      CHECK(snd.bounds.intersects(fst.bounds));
    }

    SUBCASE("Bounds intersection but no actual subhitbox intersection")
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

      const auto fst = hitbox::create({{{}, FRect{{100, 100}, {75, 100}}},
                                       {{}, FRect{{175, 100}, {25, 25}}}});

      const auto snd = hitbox::create({{{}, FRect{{210, 150}, {100, 100}}},
                                       {{}, FRect{{150, 210}, {25, 25}}}});

      REQUIRE(fst.bounds.intersects(snd.bounds));
      REQUIRE(snd.bounds.intersects(fst.bounds));

      CHECK(!hitbox::intersects(fst, snd));
      CHECK(!hitbox::intersects(snd, fst));
    }
  }
}