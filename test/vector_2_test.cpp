#include "catch.hpp"
#include "vector_2.h"

using namespace wanderer::core;

TEST_CASE("Vector2DefaultCtor", "[Vector2]") {
  Vector2 vector; // should be (0, 0)
  CHECK(vector.GetX() == 0);
  CHECK(vector.GetY() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2Ctor", "[Vector2]") {
  float x = 53.8;
  float y = 125.2;
  auto vector = Vector2(x, y);

  CHECK(vector.GetX() == x);
  CHECK(vector.GetY() == y);
  CHECK(!vector.IsZero());
}

TEST_CASE("Vector2CopyCtor", "[Vector2]") {
  auto original = Vector2(87.3f, 39.5f);
  auto copy = Vector2(original);

  CHECK(original.GetX() == copy.GetX());
  CHECK(original.GetY() == copy.GetY());
}

TEST_CASE("Vector2::Scale", "[Vector2]") {
  float x = 24.5f;
  float y = 83.7f;
  Vector2 vector(x, y);

  float factor = 3.2f;
  vector.Scale(factor);

  CHECK(vector.GetX() == Approx(x * factor));
  CHECK(vector.GetY() == Approx(y * factor));

  vector.Scale(0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::Norm", "[Vector2]") {
  Vector2 vector(12.0f, 92.3f);

  vector.Norm();

  CHECK(vector.IsUnit());
  CHECK(vector.GetLength() == Approx(1));
}

TEST_CASE("Vector2::SetLength", "[Vector2]") {
  Vector2 vector(52, 93);

  float length = 4;
  vector.SetLength(length);
  CHECK(vector.GetLength() == Approx(length));
}

TEST_CASE("Vector2::GetLength", "[Vector2]") {
  Vector2 vector;

  CHECK(vector.GetLength() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::GetLength2", "[Vector2]") {
  Vector2 vector;

  CHECK(vector.GetLength2() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::IsZero", "[Vector2]") {
  Vector2 first;
  CHECK(first.IsZero());

  Vector2 other(12, 95);
  CHECK(!other.IsZero());
}

TEST_CASE("Vector2::IsUnit", "[Vector2]") {
  Vector2 vector(1, 0);
  CHECK(vector.IsUnit());

  vector.Scale(0.5f);
  CHECK(!vector.IsUnit());

  vector.Norm();
  CHECK(vector.IsUnit());
}
