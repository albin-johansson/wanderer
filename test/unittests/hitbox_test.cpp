#include "catch.hpp"
#include "hitbox.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Hitbox::AddRectangle", "[Hitbox]") {
  SECTION("A hitbox with only one rectangle has the rectangle as its bounds.") {
    Rectangle rect(10, 10, 100, 160);

    Hitbox hitbox;
    hitbox.AddRectangle(rect, {0, 0});

    CHECK(hitbox.GetBounds().GetX() == rect.GetX());
    CHECK(hitbox.GetBounds().GetY() == rect.GetY());
    CHECK(hitbox.GetBounds().GetWidth() == rect.GetWidth());
    CHECK(hitbox.GetBounds().GetHeight() == rect.GetHeight());
  }

  SECTION("Multiple subhitboxes 1") {
    /*
     * Rough visualisation of the test.
     *  _ _ _ _ _
     * |         |_ _ _
     * |_ _ _ _ _|     |
     *           |     |
     *           |_ _ _|
     */
    Rectangle fst(10, 10, 140, 50);
    Rectangle snd(fst.GetMaxX(), 80, 50, fst.GetWidth());

    Hitbox hitbox;

    hitbox.AddRectangle(fst, {0, 0});
    hitbox.AddRectangle(snd, {0, 0});

    const auto& bounds = hitbox.GetBounds();

    CHECK(bounds.GetX() == fst.GetX());
    CHECK(bounds.GetY() == fst.GetY());
    CHECK(bounds.GetWidth() == (fst.GetWidth() + snd.GetWidth()));
    CHECK(bounds.GetHeight() == 50 + 140 - 70);
  }

  SECTION("Multiple subhitboxes 2") {
    /*
     * Rough visualisation of the test.
     *  _ _ _ _ _
     * |         |  _ _ _
     * |_ _ _ _ _| |     |
     *             |     |
     *             |_ _ _|
     */
    Rectangle fst(10, 10, 140, 50);
    Rectangle snd(fst.GetMaxX() + 10,
                  fst.GetY() + (fst.GetHeight() / 2),
                  50, fst.GetWidth());

    Hitbox hitbox;

    hitbox.AddRectangle(fst, {0, 0});
    hitbox.AddRectangle(snd, {0, 0});

    const auto& bounds = hitbox.GetBounds();

    CHECK(bounds.GetX() == fst.GetX());
    CHECK(bounds.GetY() == fst.GetY());
//    CHECK(bounds.GetWidth() == (fst.GetWidth() + snd.GetWidth() + 10));
//    CHECK(bounds.GetHeight() == (fst.GetHeight() + snd.GetHeight()));
  }
}

//TEST_CASE("Hitbox::Intersects", "[Hitbox]") {
//  Hitbox hitbox;
//
//  Rectangle rect(10, 10, 100, 160);
//
//  CHECK(hitbox.GetBounds().GetX() == rect.GetX());
//  CHECK(hitbox.GetBounds().GetY() == rect.GetY());
//  CHECK(hitbox.GetBounds().GetWidth() == rect.GetWidth());
//  CHECK(hitbox.GetBounds().GetHeight() == rect.GetHeight());
//}