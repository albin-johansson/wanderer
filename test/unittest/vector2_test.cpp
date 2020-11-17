#include "vector2.hpp"

#include <catch.hpp>

#include "angles.hpp"

using namespace wanderer;

TEST_CASE("vector2f default values", "[vector2f]")
{
  const vector2f vec;
  CHECK(vec.x == 0);
  CHECK(vec.y == 0);
  CHECK(vec.is_zero());
  CHECK(vec.magnitude() == 0);
}

TEST_CASE("vector2f ctor", "[vector2f]")
{
  const auto x = 112.9f;
  const auto y = 8254.3f;

  const vector2f vec{x, y};

  CHECK(vec.x == x);
  CHECK(vec.y == y);
}

TEST_CASE("vector2f::scale", "[vector2f]")
{
  vector2f vector;

  vector.scale(7);  // scaling zeroed vector
  CHECK(vector.is_zero());

  const auto x = 745;
  const auto y = -1834;
  vector.x = x;
  vector.y = y;

  CHECK(vector.x == x);
  CHECK(vector.y == y);

  const auto scale = 82;
  vector.scale(scale);

  CHECK(vector.x == x * scale);
  CHECK(vector.y == y * scale);
}

TEST_CASE("vector2f::norm", "[vector2f]")
{
  SECTION("Normalize the zero vector")
  {
    vector2f vector;
    vector.norm();  // no effect on the zero vector
    CHECK(!vector.is_unit());
    CHECK(vector.is_zero());
  }

  SECTION("Normalize non-zero vector")
  {
    vector2f vector{42, 124};
    CHECK(!vector.is_unit());

    vector.norm();
    CHECK(vector.is_unit());
  }
}

TEST_CASE("vector2f::zero", "[vector2f]")
{
  vector2f vector{849, 241};
  CHECK(!vector.is_zero());

  vector.zero();
  CHECK(vector.is_zero());
}

TEST_CASE("vector2f::set_magnitude", "[vector2f]")
{
  SECTION("Normal magnitude")
  {
    vector2f vector{1283, 881};
    vector.set_magnitude(433);
    CHECK(vector.magnitude() == Approx(433));
  }

  SECTION("Create unit vector")
  {
    vector2f vector{849, 241};
    vector.set_magnitude(1);
    CHECK(vector.is_unit());
  }

  SECTION("Zero magnitude")
  {
    vector2f vector{849, 241};
    vector.set_magnitude(0);
    CHECK(vector.is_zero());
  }

  SECTION("Negative magnitude")
  {
    vector2f vector{849, 241};
    vector.set_magnitude(-1);
    CHECK(vector.is_zero());
  }
}

TEST_CASE("vector2f::lerp", "[vector2f]")
{
  const auto x = 123;
  const auto y = 456;
  vector2f fst{x, y};
  const vector2f snd{834, 432};

  const auto alpha = 0.8;
  const auto ialpha = 1 - alpha;

  fst.lerp(snd, alpha);

  CHECK(fst.x == Approx(x * ialpha + snd.x * alpha));
  CHECK(fst.y == Approx(y * ialpha + snd.y * alpha));
}

TEST_CASE("vector2f::lerp_smooth", "[vector2f]")
{
  vector2f fst{123, 456};
  const vector2f snd{834, 432};
  CHECK_NOTHROW(fst.lerp_smooth(snd, 0.45));  // just check that it compiles
}

// TODO point_at

TEST_CASE("vector2f::negate", "[vector2f]")
{
  vector2f vector{20, 30};

  vector.negate();
  CHECK(vector.x == -20);
  CHECK(vector.y == -30);

  vector.negate();
  CHECK(vector.x == 20);
  CHECK(vector.y == 30);
}

TEST_CASE("vector2f::operator+=", "[vector2f]")
{
  const auto x = 20;
  const auto y = 30;

  vector2f fst{x, y};
  const vector2f snd{45, -14};

  fst += snd;

  CHECK(fst.x == x + snd.x);
  CHECK(fst.y == y + snd.y);
}

TEST_CASE("vector2f::operator-=", "[vector2f]")
{
  const auto x = 83;
  const auto y = 55;

  vector2f fst{x, y};
  const vector2f snd{-35, 77};

  fst -= snd;

  CHECK(fst.x == x - snd.x);
  CHECK(fst.y == y - snd.y);
}

TEST_CASE("vector2f::distance", "[vector2f]")
{
  SECTION("Distance to self")
  {
    const vector2f vector{783, 334};
    CHECK(distance(vector, vector) == 0);
  }

  SECTION("Normal vectors")
  {
    const vector2f fst{1892, 4412};
    const vector2f snd{442, 266};

    const auto expected = 4392.24;  // obtained from wolfram alpha

    CHECK(distance(fst, snd) == Approx(expected));
    CHECK(distance(snd, fst) == Approx(expected));
  }
}

TEST_CASE("vector2f::cross", "[vector2f]")
{
  const vector2f fst{123, 456};
  const vector2f snd{789, 434};
  CHECK(cross(fst, fst) == 0);

  // Expected values obtained from wolfram alpha
  CHECK(cross(fst, snd) == -306'402);
  CHECK(cross(snd, fst) == 306'402);
}

TEST_CASE("vector2f::angle", "[vector2f]")
{
  SECTION("Angle to self")
  {
    const vector2f vector{1283, 9123};
    CHECK(angle(vector, vector) == 0);
  }

  SECTION("Non-zero vectors")
  {
    SECTION("Small vectors")
    {
      const vector2f fst{50, 25};
      const vector2f snd{5, 10};

      // Obtained with wolfram alpha
      const auto expected = std::acos(4.0 / 5.0);

      CHECK(angle(fst, snd) == Approx(expected));
      CHECK(angle(snd, fst) == Approx(-expected));
    }

    SECTION("Big vectors")
    {
      const vector2f fst{63'112, 58'124};
      const vector2f snd{30'979, 77'437};

      // Obtained with wolfram alpha
      const auto expected =
          0.5 * (pi<double> - 2 * std::atan(1614023709.0 / 771645137.0));

      CHECK(angle(fst, snd) == Approx(expected));
      CHECK(angle(snd, fst) == Approx(-expected));
    }
  }

  SECTION("With the zero vector")
  {
    const vector2f zero;
    const vector2f nonZero{123, 123};
    CHECK(angle(zero, zero) == 0);
    CHECK(angle(zero, nonZero) == 0);
    CHECK(angle(nonZero, zero) == 0);
  }
}

TEST_CASE("vector2f::operator+", "[vector2f]")
{
  const vector2f fst(25, 83);
  const vector2f snd(93, 12);
  const auto sum = fst + snd;
  CHECK(sum.x == fst.x + snd.x);
  CHECK(sum.y == fst.y + snd.y);
}

TEST_CASE("vector2f::operator-", "[vector2f]")
{
  const vector2f fst(831, -472);
  const vector2f snd(185, 442);

  const auto diff1 = fst - snd;
  const auto diff2 = snd - fst;

  CHECK(diff1.x == fst.x - snd.x);
  CHECK(diff1.y == fst.y - snd.y);

  CHECK(diff2.x == snd.x - fst.x);
  CHECK(diff2.y == snd.y - fst.y);
}
