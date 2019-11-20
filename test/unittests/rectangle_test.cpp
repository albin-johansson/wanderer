#include "catch.hpp"
#include "rectangle.h"

using namespace wanderer::core;

TEST_CASE("Rectangle()", "[Rectangle]") {
  Rectangle r;

  CHECK(r.GetX() == 0);
  CHECK(r.GetY() == 0);
  CHECK(r.GetWidth() == 10);
  CHECK(r.GetHeight() == 10);
}

TEST_CASE("Rectangle(float, float, int, int)", "[Rectangle]") {
  float x = 24.4;
  float y = -2.5;
  float width = 92.3;
  float height = 27;
  Rectangle r(x, y, width, height);

  CHECK(r.GetX() == x);
  CHECK(r.GetY() == y);
  CHECK(r.GetWidth() == width);
  CHECK(r.GetHeight() == height);

  CHECK_THROWS_AS(Rectangle(0, 0, 0, 1), std::invalid_argument);
  CHECK_THROWS_AS(Rectangle(0, 0, 1, 0), std::invalid_argument);
}

TEST_CASE("Rectangle(Rectangle&)", "[Rectangle]") {
  float x = 72.2;
  float y = 33.9;
  int width = 48;
  int height = 31;
  Rectangle rect(x, y, width, height);

  Rectangle copy(rect);
  CHECK(rect.GetX() == copy.GetX());
  CHECK(rect.GetY() == copy.GetY());
  CHECK(rect.GetWidth() == copy.GetWidth());
  CHECK(rect.GetHeight() == copy.GetHeight());
}

TEST_CASE("Rectangle::MoveX", "[Rectangle]") {
  float x = 41.2;
  Rectangle rect(x, 10, 10, 10);

  float dx = 24;
  rect.MoveX(dx);

  CHECK(rect.GetX() == Approx(x + dx));
}

TEST_CASE("Rectangle::MoveY", "[Rectangle]") {
  float y = 77.6;
  Rectangle rect(10, y, 10, 10);

  float dy = 4.5;
  rect.MoveY(dy);

  CHECK(rect.GetY() == Approx(y + dy));
}

TEST_CASE("Rectangle::Contains", "[Rectangle]") {
  SECTION("Edge case when the point is positioned on the edge of the rectangle") {
    Rectangle rect(10, 10, 10, 10);
    CHECK(rect.Contains(rect.GetX(), rect.GetY()));
    CHECK(rect.Contains(rect.GetMaxX(), rect.GetY()));
    CHECK(rect.Contains(rect.GetX(), rect.GetMaxY()));
    CHECK(rect.Contains(rect.GetMaxX(), rect.GetMaxY()));
  }

  SECTION("Not contained") {
    Rectangle rect(10, 10, 10, 10);
    CHECK(!rect.Contains(rect.GetX() - 1, rect.GetY()));
    CHECK(!rect.Contains(rect.GetX(), rect.GetY() - 1));
    CHECK(!rect.Contains(rect.GetMaxX() + 1, rect.GetY()));
    CHECK(!rect.Contains(rect.GetX(), rect.GetMaxY() + 1));
  }

  Rectangle rect(10, 10, 10, 10);
  CHECK(rect.Contains(rect.GetX() + 5, rect.GetY() + 5));
}

TEST_CASE("Rectangle::Intersects", "[Rectangle]") {
  SECTION("Same coordinates") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(r1.GetX(), r1.GetY(), 50, 50);
    CHECK(r1.Intersects(r2));
    CHECK(r2.Intersects(r1));
  }

  SECTION("Normal intersection") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(30, 23, 25, 80);
    CHECK(r1.Intersects(r2));
    CHECK(r2.Intersects(r1));
  }

  SECTION("Edge case where rectangles are next to each other horizontally") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(r1.GetMaxX(), 10, 50, 50);
    CHECK(!r1.Intersects(r2));
    CHECK(!r2.Intersects(r1));
  }

  SECTION("Edge case where rectangles are next to each other vertically") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(10, r1.GetMaxY(), 50, 50);
    CHECK(!r1.Intersects(r2));
    CHECK(!r2.Intersects(r1));
  }

  SECTION("No intersection horizontally") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(r1.GetMaxX() + 1, 10, 50, 50);

    CHECK(!r1.Intersects(r2));
    CHECK(!r2.Intersects(r1));
  }

  SECTION("No intersection vertically") {
    Rectangle r1(10, 10, 50, 50);
    Rectangle r2(10, r1.GetMaxY() + 1, 50, 50);

    CHECK(!r1.Intersects(r2));
    CHECK(!r2.Intersects(r1));
  }
}

TEST_CASE("Rectangle::GetMaxX", "[Rectangle]") {
  float x = 20;
  int width = 50;
  Rectangle rect(x, 10, width, 10);

  CHECK(rect.GetMaxX() == (x + width));
}

TEST_CASE("Rectangle::GetMaxY", "[Rectangle]") {
  float y = 14;
  int height = 48;
  Rectangle rect(10, y, 10, height);

  CHECK(rect.GetMaxY() == (y + height));
}

TEST_CASE("Rectangle::SetWidth", "[Rectangle]") {
  Rectangle rect;
  CHECK_THROWS_AS(rect.SetWidth(0), std::invalid_argument);
  CHECK_THROWS_AS(rect.SetWidth(-1), std::invalid_argument);
}

TEST_CASE("Rectangle::SetHeight", "[Rectangle]") {
  Rectangle rect;
  CHECK_THROWS_AS(rect.SetHeight(0), std::invalid_argument);
  CHECK_THROWS_AS(rect.SetHeight(-1), std::invalid_argument);
}