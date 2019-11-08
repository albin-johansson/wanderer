#include "catch.hpp"
#include "objects.h"

using namespace wanderer::core;

TEST_CASE("Objects::RequireNonNull(T*)", "[Objects]") {
  int* badPtr = nullptr;
  CHECK_THROWS_AS(Objects::RequireNonNull(badPtr), Objects::NullPointerException);

  int a = 12;
  int* goodPtr = &a;
  CHECK_NOTHROW(Objects::RequireNonNull(goodPtr));
}

TEST_CASE("Objects::RequireNonNull(std::shared_ptr<T>)", "[Objects]") {
  std::shared_ptr<int> badPtr = nullptr;
  CHECK_THROWS_AS(Objects::RequireNonNull(badPtr), Objects::NullPointerException);

  int a = 12;
  auto goodPtr = std::shared_ptr<int>(&a);
  CHECK_NOTHROW(Objects::RequireNonNull(goodPtr));
}

TEST_CASE("Objects::RequireNonNull(std::unique_ptr<T>)", "[Objects]") {
  std::unique_ptr<int> badPtr = nullptr;
  CHECK_THROWS_AS(Objects::RequireNonNull(std::move(badPtr)), Objects::NullPointerException);

  int a = 12;
  auto goodPtr = std::unique_ptr<int>(&a);
  CHECK_NOTHROW(Objects::RequireNonNull(std::move(goodPtr)));
}