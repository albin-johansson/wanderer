#include "hitbox.h"

#include <doctest.h>

using namespace wanderer;
using namespace centurion;

TEST_SUITE("Hitbox")
{
  TEST_CASE("add_rectangle")
  {
    Hitbox hitbox;

    const FRect rect{{56.2f, 128.5f}, {156.3f, 100.6f}};
    const Vector2f offset{24.5f, 52.9f};
    hitbox.add_rectangle(rect, offset);

    CHECK(hitbox.is_unit());
    CHECK(hitbox.bounds() == rect);
  }

  TEST_CASE("set_x")
  {
    Hitbox hitbox;

    const auto x = 839.2f;
    hitbox.set_x(x);

    CHECK(hitbox.bounds().x() == x);
  }

  TEST_CASE("set_y")
  {
    Hitbox hitbox;

    const auto y = -421.8f;
    hitbox.set_y(y);

    CHECK(hitbox.bounds().y() == y);
  }

  TEST_CASE("Bounds test with two rectangles")
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
    hitbox.set_enabled(true);

    const FRect first = {{10, 10}, {100, 100}};
    const FRect second = {{first.max_x() + 10, first.max_y() + 10}, {100, 100}};

    hitbox.add_rectangle(first, {0, 0});
    hitbox.add_rectangle(second, {0, 0});

    const FRect expected = {
        {first.x(), first.y()},
        {second.max_x() - first.x(), second.max_y() - first.y()}};

    CHECK(hitbox.bounds() == expected);
  }

  TEST_CASE("Test of valid intersection")
  {
    /*
     * Rough visualisation of the test.
     *  ___
     * |  _|__
     * |_|_| |
     *   |___|
     *
     */

    Hitbox first;
    first.set_enabled(true);
    first.add_rectangle({{100, 100}, {100, 100}}, {});

    Hitbox second;
    second.set_enabled(true);
    second.add_rectangle({{150, 150}, {100, 100}}, {});

    CHECK(first.intersects(second));
    CHECK(second.intersects(first));

    CHECK(first.intersects(second.bounds()));
    CHECK(second.intersects(first.bounds()));
  }

  TEST_CASE("set_enabled")
  {
    Hitbox hitbox;

    hitbox.set_enabled(true);
    CHECK(hitbox.is_enabled());

    hitbox.set_enabled(false);
    CHECK(!hitbox.is_enabled());
  }
}