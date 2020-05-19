#include "vector_2.h"

#include <cmath>

#include "catch.hpp"

using namespace wanderer;

// TODO improve tests

TEST_CASE("Vector2DefaultCtor", "[Vector2]")
{
  Vector2 vector;  // should be (0, 0)
  CHECK(vector.x == 0);
  CHECK(vector.y == 0);
  CHECK(vector.is_zero());
}

TEST_CASE("Vector2Ctor", "[Vector2]")
{
  float x = 53.8;
  float y = 125.2;
  auto vector = Vector2(x, y);

  CHECK(vector.x == x);
  CHECK(vector.y == y);
  CHECK(!vector.is_zero());
}

TEST_CASE("Vector2CopyCtor", "[Vector2]")
{
  auto original = Vector2(87.3f, 39.5f);
  auto copy = Vector2(original);

  CHECK(original.x == copy.x);
  CHECK(original.y == copy.y);
}

TEST_CASE("Vector2::Scale", "[Vector2]")
{
  float x = 24.5f;
  float y = 83.7f;
  Vector2 vector(x, y);

  float factor = 3.2f;
  vector.scale(factor);

  CHECK(vector.x == Approx(x * factor));
  CHECK(vector.y == Approx(y * factor));

  vector.scale(0);
  CHECK(vector.is_zero());
}

TEST_CASE("Vector2::operator+", "[Vector2]")
{
  const Vector2 lhs(123.4f, 614.9f);
  const Vector2 rhs(981.1f, -234.7f);

  Vector2 res1 = lhs + rhs;
  Vector2 res2 = rhs + lhs;

  CHECK(((res1.x == (lhs.x + rhs.x)) && (res2.x == (lhs.x + rhs.x))));
  CHECK(((res1.y == (lhs.y + rhs.y)) && (res2.y == (lhs.y + rhs.y))));
}

TEST_CASE("Vector2::operator-", "[Vector2]")
{
  const Vector2 lhs(517.9f, 1774);
  const Vector2 rhs(181.1f, 734.2f);

  SECTION("Normal operator test")
  {
    Vector2 res1 = lhs - rhs;

    CHECK(res1.x == (lhs.x - rhs.x));
    CHECK(res1.y == (lhs.y - rhs.y));
  }

  SECTION("Reversed operands")
  {
    Vector2 res2 = rhs - lhs;

    CHECK(res2.x == (rhs.x - lhs.x));
    CHECK(res2.y == (rhs.y - lhs.y));
  }
}

TEST_CASE("Vector2::operator==", "[Vector2]")
{
  Vector2 vector(712.8f, 913.3f);
  Vector2 copy(vector);
  Vector2 other(193.f, 385.f);

  CHECK(vector == vector);
  CHECK(vector == copy);
  CHECK(copy == vector);
  CHECK(!(vector == other));
}

TEST_CASE("Vector2::operator!=", "[Vector2]")
{
  Vector2 vector(389.4f, 4143.3f);
  Vector2 copy(vector);
  Vector2 other(-133.3f, 471.5f);

  CHECK(!(vector != vector));
  CHECK(!(vector != copy));
  CHECK(!(copy != vector));
  CHECK(vector != other);
}

TEST_CASE("Vector2::Add1", "[Vector2]")
{
  float x = 19.9f;
  float y = 27.2f;
  Vector2 vector(x, y);

  float dx = 53;
  float dy = -23;

  Vector2 other(dx, dy);
  vector.add(other);

  CHECK(other.x == dx);
  CHECK(other.y == dy);

  CHECK(vector.x == Approx(x + dx));
  CHECK(vector.y == Approx(y + dy));
}

TEST_CASE("Vector2::Add2", "[Vector2]")
{
  float x = 44.1f;
  float y = 38.6f;
  Vector2 vector(x, y);

  float dx = -29;
  float dy = 12;

  vector.add(dx, dy);
  CHECK(vector.x == Approx(x + dx));
  CHECK(vector.y == Approx(y + dy));
}

TEST_CASE("Vector2::Sub", "[Vector2]")
{
  float x = 24.5f;
  float y = 83.7f;
  Vector2 vector(x, y);

  float x1 = 88.2f;
  float y1 = 24.8f;

  Vector2 other(x1, y1);

  vector.sub(other);
  CHECK(vector.x == Approx(x - x1));
  CHECK(vector.y == Approx(y - y1));
}

TEST_CASE("Vector2::Norm", "[Vector2]")
{
  Vector2 vector(12.0f, 92.3f);

  vector.norm();

  CHECK(vector.is_unit());
  CHECK(vector.get_length() == Approx(1));
}

TEST_CASE("Vector2::Zero", "[Vector2]")
{
  Vector2 vector(859.0f, 229.3f);

  vector.zero();
  CHECK(vector.is_zero());
}

TEST_CASE("Vector2::Set", "[Vector2]")
{
  Vector2 vector(91, 3);
  Vector2 other(123, 45);

  vector.set(other);

  CHECK(vector.x == Approx(other.x));
  CHECK(vector.y == Approx(other.y));
}

TEST_CASE("Vector2::SetLength", "[Vector2]")
{
  Vector2 vector(52, 93);

  float length = 4;
  vector.set_length(length);
  CHECK(vector.get_length() == Approx(length));
}

TEST_CASE("Vector2::LookAt(Vector2, float)", "[Vector2]")
{
  Vector2 vector(412, 287);

  CHECK_NOTHROW(vector.look_at(vector, 0));
  CHECK_NOTHROW(vector.look_at(vector, -1));
}

TEST_CASE("Vector2::DistanceTo", "[Vector2]")
{
  Vector2 vector(377, 518);
  Vector2 other(123, 411);

  auto dx = other.x - vector.x;
  auto dy = other.y - vector.y;
  auto expected = std::sqrt(dx * dx + dy * dy);
  CHECK(expected == vector.distance_to(other));
  CHECK(vector.distance_to(other) == other.distance_to(vector));

  CHECK(vector.distance_to(vector) == 0);
}

TEST_CASE("Vector2::DistanceTo2", "[Vector2]")
{
  Vector2 vector(58, 832);
  Vector2 other(284, 550);

  CHECK(std::sqrt(vector.distance_to_2(other)) == vector.distance_to(other));
  CHECK(vector.distance_to_2(vector) == 0);
}

TEST_CASE("Vector2::Angle", "[Vector2]")
{
  const Vector2 nx(-1, 0);
  const Vector2 ny(0, -1);

  CHECK(xUnit.angle(yUnit) == 90);
  CHECK(yUnit.angle(xUnit) == 90);
  CHECK(xUnit.angle(ny) == 90);
  CHECK(yUnit.angle(nx) == 90);

  CHECK(xUnit.angle(xUnit) == 0);

  SECTION("Maximum possible angle")
  {
    CHECK(nx.angle(xUnit) == 180);
    CHECK(xUnit.angle(nx) == 180);
  }

  SECTION("1 degree step")
  {
    Vector2 v(std::cos(Math::to_radians(1.0f)),
              std::sin(Math::to_radians(1.0f)));
    CHECK(xUnit.angle(v) == 1);
  }
}

TEST_CASE("Vector2::Invert", "[Vector2]")
{
  const auto x = 4;
  const auto y = 8;

  Vector2 vector(x, y);
  vector.invert();

  CHECK(vector.x == (-1 * x));
  CHECK(vector.y == (-1 * y));
}

TEST_CASE("Vector2::GetLength", "[Vector2]")
{
  Vector2 vector;

  CHECK(vector.get_length() == 0);
  CHECK(vector.is_zero());

  CHECK(xUnit.get_length() == 1);
  CHECK(xUnit.is_unit());

  CHECK(yUnit.get_length() == 1);
  CHECK(yUnit.is_unit());
}

TEST_CASE("Vector2::GetLength2", "[Vector2]")
{
  Vector2 vector;

  CHECK(vector.get_length_2() == 0);
  CHECK(vector.is_zero());
}

TEST_CASE("Vector2::IsZero", "[Vector2]")
{
  Vector2 first;
  CHECK(first.is_zero());

  Vector2 other(12, 95);
  CHECK(!other.is_zero());
}

TEST_CASE("Vector2::IsUnit", "[Vector2]")
{
  Vector2 vector(1, 0);
  CHECK(vector.is_unit());

  vector.scale(0.5f);
  CHECK(!vector.is_unit());

  vector.norm();
  CHECK(vector.is_unit());
}
