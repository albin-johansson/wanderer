#include "hitbox.hpp"

#include <gtest/gtest.h>

#include "centurion_utils.hpp"
#include "hitbox_system.hpp"
#include "movable.hpp"

using namespace wanderer;

TEST(Hitbox, UpdateBounds)
{
  {  // One hitbox
    comp::hitbox hb;

    const float2 origin{25, 17};
    const float2 offset{10, 12};
    const cen::farea size{90, 85};

    hb.origin = origin;
    hb.boxes.push_back(comp::subhitbox{offset, size});

    sys::update_bounds(hb);
    EXPECT_EQ(cen::frect(to_point(origin + offset), size), hb.bounds);
  }

  {  // Two hitboxes
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

    const float2 offsetA{10, 12};
    const float2 offsetB{120, 120};

    const cen::farea sizeA{90, 85};
    const cen::farea sizeB{105, 109};

    const comp::subhitbox fst{offsetA, sizeA};
    const comp::subhitbox snd{offsetB, sizeB};

    hb.boxes.push_back(fst);
    hb.boxes.push_back(snd);

    sys::update_bounds(hb);

    EXPECT_EQ(offsetA, hb.boxes.at(0).offset);
    EXPECT_EQ(sizeA, hb.boxes.at(0).size);

    EXPECT_EQ(offsetB, hb.boxes.at(1).offset);
    EXPECT_EQ(sizeB, hb.boxes.at(1).size);

    const cen::frect expected{{10, 12}, {215, 217}};
    EXPECT_EQ(expected, hb.bounds);
    EXPECT_EQ(float2{}, hb.origin);
  }
}

TEST(Hitbox, Intersects)
{
  {  // Valid intersections
    /*
     * Rough visualisation of the test.
     *  ___
     * |  _|__
     * |_|_| |
     *   |___|
     *
     */

    const auto fst = sys::create_hitbox({{{100, 100}, {100, 100}}});
    const auto snd = sys::create_hitbox({{{150, 150}, {100, 100}}});

    EXPECT_TRUE(sys::intersects(fst, snd));
    EXPECT_TRUE(sys::intersects(snd, fst));

    EXPECT_TRUE(cen::intersects(fst.bounds, snd.bounds));
    EXPECT_TRUE(cen::intersects(snd.bounds, fst.bounds));
  }

  {  // Bounds intersection but no actual subhitbox intersection

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
        sys::create_hitbox({{{100, 100}, {75, 100}}, {{175, 100}, {25, 25}}});

    const auto snd =
        sys::create_hitbox({{{210, 150}, {100, 100}}, {{150, 210}, {25, 25}}});

    ASSERT_TRUE(cen::intersects(fst.bounds, snd.bounds));
    ASSERT_TRUE(cen::intersects(snd.bounds, fst.bounds));

    EXPECT_FALSE(sys::intersects(fst, snd));
    EXPECT_FALSE(sys::intersects(snd, fst));
  }
}

TEST(Hitbox, Create)
{
  {  // One hitbox
    const float2 offset{12, 34};
    const cen::farea size{150, 100};
    const auto hb = sys::create_hitbox({{offset, size}});

    EXPECT_FLOAT_EQ(offset.x, hb.bounds.x());
    EXPECT_FLOAT_EQ(offset.y, hb.bounds.y());
    EXPECT_FLOAT_EQ(size.width, hb.bounds.width());
    EXPECT_FLOAT_EQ(size.height, hb.bounds.height());
  }

  {  // One hitbox with two subhitboxes
    const auto hb = sys::create_hitbox({{{2, 0}, {32, 28}}, {{16, 22}, {36, 32}}});

    EXPECT_FLOAT_EQ(2, hb.bounds.x());
    EXPECT_FLOAT_EQ(0, hb.bounds.y());
    EXPECT_FLOAT_EQ(50, hb.bounds.width());
    EXPECT_FLOAT_EQ(54, hb.bounds.height());
  }

  {  // Two hitboxes
    const float2 offset1{10, 20};
    const float2 offset2{5, 10};

    const cen::farea size1{25, 40};
    const cen::farea size2{40, 60};

    const auto hb = sys::create_hitbox({{offset1, size1}, {offset2, size2}});

    EXPECT_FLOAT_EQ(5, hb.bounds.x());
    EXPECT_FLOAT_EQ(10, hb.bounds.y());

    EXPECT_FLOAT_EQ(40, hb.bounds.width());
    EXPECT_FLOAT_EQ(60, hb.bounds.height());
  }
}
