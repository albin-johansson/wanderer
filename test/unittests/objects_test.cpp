#include "catch.hpp"
#include "require.h"
#include "vector_2.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Objects::RequireNonNull(T*)", "[Objects]") {
  Vector2* badPtr = nullptr;
  CHECK_THROWS_AS(Require::not_null(badPtr), Require::NullPointerException);

  Vector2 vec(0, 0);
  auto goodPtr = &vec;
  CHECK_NOTHROW(Require::not_null(goodPtr));
}

TEST_CASE("Objects::RequireNonNull(std::shared_ptr<T>)", "[Objects]") {
  std::shared_ptr<Vector2> badPtr = nullptr;
  CHECK_THROWS_AS(Require::not_null(badPtr), Require::NullPointerException);

  Vector2 vec(0, 0);
  auto goodPtr = std::shared_ptr<Vector2>(&vec);
  CHECK_NOTHROW(Require::not_null(goodPtr));
}

TEST_CASE("Objects::RequireNonNull(std::unique_ptr<T>)", "[Objects]") {
  std::unique_ptr<Vector2> badPtr = nullptr;
  CHECK_THROWS_AS(Require::not_null(std::move(badPtr)), Require::NullPointerException);

  Vector2 vec(0, 0);
  auto goodPtr = std::unique_ptr<Vector2>(&vec);
  CHECK_NOTHROW(Require::not_null(std::move(goodPtr)));
}