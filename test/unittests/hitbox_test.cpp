#include "catch.hpp"
#include "hitbox.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Hitbox::AddRectangle", "[Hitbox]") {
  SECTION("A hitbox with only one rectangle has the rectangle as its bounds.") {
    FRectangle rect(10, 10, {100, 160});

    Hitbox hitbox;
    hitbox.add_rectangle(rect, {0, 0});

    CHECK(hitbox.get_bounds().GetX() == rect.GetX());
    CHECK(hitbox.get_bounds().GetY() == rect.GetY());
    CHECK(hitbox.get_bounds().GetWidth() == rect.GetWidth());
    CHECK(hitbox.get_bounds().GetHeight() == rect.GetHeight());
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
    FRectangle fst(10, 10, {140, 50});
    FRectangle snd(fst.GetMaxX(), 80, {50, fst.GetWidth()});

    Hitbox hitbox;

    hitbox.add_rectangle(fst, {0, 0});
    hitbox.add_rectangle(snd, {0, 0});

    const auto& bounds = hitbox.get_bounds();

    CHECK(bounds.GetX() == fst.GetX());
    CHECK(bounds.GetY() == fst.GetY());
    CHECK(bounds.GetWidth() == (fst.GetWidth() + snd.GetWidth()));
//    CHECK(bounds.GetHeight() == 50 + 140 - 70);
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
    FRectangle fst(10, 10, {140, 50});
    FRectangle snd(fst.GetMaxX() + 10,
                   fst.GetY() + (fst.GetHeight() / 2),
                   {50, fst.GetWidth()});

    Hitbox hitbox;

    hitbox.add_rectangle(fst, {0, 0});
    hitbox.add_rectangle(snd, {0, 0});

    const auto& bounds = hitbox.get_bounds();

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