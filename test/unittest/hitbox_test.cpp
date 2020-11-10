#include "component/hitbox.hpp"

#include <catch.hpp>

#include "centurion_utils.hpp"
#include "component/movable.hpp"
#include "hitbox_system.hpp"

using namespace wanderer;

TEST_CASE("hitbox::update_bounds", "[hitbox]")
{
  SECTION("One hitbox")
  {
    comp::hitbox hb;

    const vector2f origin{25, 17};
    const vector2f offset{10, 12};
    const cen::farea size{90, 85};

    hb.origin = origin;
    hb.boxes.push_back(comp::subhitbox{offset, size});

    sys::hitbox::update_bounds(hb);

    CHECK(hb.bounds == cen::frect{to_point(origin + offset), size});
  }

  SECTION("Two hitboxes")
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
    comp::hitbox hb;

    const vector2f offsetA{10, 12};
    const vector2f offsetB{120, 120};

    const cen::farea sizeA{90, 85};
    const cen::farea sizeB{105, 109};

    const comp::subhitbox fst{offsetA, sizeA};
    const comp::subhitbox snd{offsetB, sizeB};

    hb.boxes.push_back(fst);
    hb.boxes.push_back(snd);

    sys::hitbox::update_bounds(hb);

    CHECK(hb.boxes.at(0).offset == offsetA);
    CHECK(hb.boxes.at(0).size == sizeA);

    CHECK(hb.boxes.at(1).offset == offsetB);
    CHECK(hb.boxes.at(1).size == sizeB);

    const cen::frect expected{{10, 12}, {215, 217}};
    CHECK(hb.bounds == expected);
    CHECK(hb.origin == vector2f{});
  }
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

    const auto fst = sys::hitbox::create({{{100, 100}, {100, 100}}});
    const auto snd = sys::hitbox::create({{{150, 150}, {100, 100}}});

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
        sys::hitbox::create({{{100, 100}, {75, 100}}, {{175, 100}, {25, 25}}});

    const auto snd =
        sys::hitbox::create({{{210, 150}, {100, 100}}, {{150, 210}, {25, 25}}});

    REQUIRE(cen::intersects(fst.bounds, snd.bounds));
    REQUIRE(cen::intersects(snd.bounds, fst.bounds));

    CHECK(!sys::hitbox::intersects(fst, snd));
    CHECK(!sys::hitbox::intersects(snd, fst));
  }
}

TEST_CASE("hitbox::create", "[hitbox]")
{
  SECTION("One hitbox")
  {
    const vector2f offset{12, 34};
    const cen::farea size{150, 100};
    const auto hb = sys::hitbox::create({{offset, size}});

    CHECK(hb.bounds.x() == offset.x());
    CHECK(hb.bounds.y() == offset.y());
    CHECK(hb.bounds.width() == size.width);
    CHECK(hb.bounds.height() == size.height);
  }

  SECTION("One hitbox with two subhitboxes")
  {
    const auto hb =
        sys::hitbox::create({{{2, 0}, {32, 28}}, {{16, 22}, {36, 32}}});

    CHECK(hb.bounds.x() == 2);
    CHECK(hb.bounds.y() == 0);
    CHECK(hb.bounds.width() == 50);
    CHECK(hb.bounds.height() == 54);
  }

  SECTION("Two hitboxes")
  {
    const vector2f offset1{10, 20};
    const vector2f offset2{5, 10};

    const cen::farea size1{25, 40};
    const cen::farea size2{40, 60};

    const auto hb = sys::hitbox::create({{offset1, size1}, {offset2, size2}});

    CHECK(hb.bounds.x() == 5);
    CHECK(hb.bounds.y() == 10);

    CHECK(hb.bounds.width() == 40);
    CHECK(hb.bounds.height() == 60);
  }
}
