#include "hitbox.h"

#include "catch.hpp"
#include "rect.h"

using namespace centurion;
using namespace albinjohansson::wanderer;

TEST_CASE("Hitbox::AddRectangle", "[Hitbox]")
{
  SECTION("A hitbox with only one rectangle has the rectangle as its bounds.")
  {
    FRect rect(10.0f, 10.0f, 100.0f, 160.0f);

    Hitbox hitbox;
    hitbox.add_rectangle(rect, {0, 0});

    CHECK(hitbox.get_bounds().x() == rect.x());
    CHECK(hitbox.get_bounds().y() == rect.y());
    CHECK(hitbox.get_bounds().width() == rect.width());
    CHECK(hitbox.get_bounds().height() == rect.height());
  }

  SECTION("Multiple subhitboxes 1")
  {
    /*
     * Rough visualisation of the test.
     *  _ _ _ _ _
     * |         |_ _ _
     * |_ _ _ _ _|     |
     *           |     |
     *           |_ _ _|
     */
    FRect fst(10.0f, 10.0f, 140.0f, 50.0f);
    FRect snd(fst.max_x(), 80.0f, 50.0f, fst.width());

    Hitbox hitbox;

    hitbox.add_rectangle(fst, {0, 0});
    hitbox.add_rectangle(snd, {0, 0});

    const auto& bounds = hitbox.get_bounds();

    CHECK(bounds.x() == fst.x());
    CHECK(bounds.y() == fst.y());
    CHECK(bounds.width() == (fst.width() + snd.width()));
    //    CHECK(bounds.GetHeight() == 50 + 140 - 70);
  }

  SECTION("Multiple subhitboxes 2")
  {
    /*
     * Rough visualisation of the test.
     *  _ _ _ _ _
     * |         |  _ _ _
     * |_ _ _ _ _| |     |
     *             |     |
     *             |_ _ _|
     */
    FRect fst(10.0f, 10.0f, 140.0f, 50.0f);
    FRect snd(fst.x() + 10, fst.y() + (fst.height() / 2), 50, fst.width());

    Hitbox hitbox;

    hitbox.add_rectangle(fst, {0, 0});
    hitbox.add_rectangle(snd, {0, 0});

    const auto& bounds = hitbox.get_bounds();

    CHECK(bounds.x() == fst.x());
    CHECK(bounds.y() == fst.y());
    //    CHECK(bounds.GetWidth() == (fst.GetWidth() + snd.GetWidth() + 10));
    //    CHECK(bounds.GetHeight() == (fst.GetHeight() + snd.GetHeight()));
  }
}

// TEST_CASE("Hitbox::Intersects", "[Hitbox]") {
//  Hitbox hitbox;
//
//  Rectangle rect(10, 10, 100, 160);
//
//  CHECK(hitbox.GetBounds().GetX() == rect.GetX());
//  CHECK(hitbox.GetBounds().GetY() == rect.GetY());
//  CHECK(hitbox.GetBounds().GetWidth() == rect.GetWidth());
//  CHECK(hitbox.GetBounds().GetHeight() == rect.GetHeight());
//}