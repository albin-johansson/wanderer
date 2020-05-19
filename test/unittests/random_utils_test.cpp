#include "random_utils.h"

#include <string>

#include "catch.hpp"

using namespace wanderer;

TEST_CASE("RandomUtils::get_int", "[RandomUtils]")
{
  SECTION(
      "Test that specifying the same min and max value returns the same value.")
  {
    for (auto i = 0; i < 10; ++i) {
      CHECK(i == RandomUtils::get_int(i, i));
    }
  }
  SECTION("Interval test")
  {
    const auto min = 0;
    const auto max = 1'000;
    for (auto i = 0; i < 100; ++i) {
      const auto x = RandomUtils::get_int(min, max);
      CHECK(x >= min);
      CHECK(x <= max);
    }
  }
}