#include "catch.hpp"
#include "random_utils.h"
#include <string>
#include <array>

using namespace albinjohansson::wanderer;

TEST_CASE("RandomUtils::get_int", "[RandomUtils]") {
  SECTION("Test that specifying the same min and max value returns the same value.") {
    for (auto i = 0; i < 10; ++i) {
      const auto x = RandomUtils::get_rand();
      CHECK(x == RandomUtils::get_int(x, x));
    }
  }
  SECTION("Interval test") {
    const auto min = 0;
    const auto max = 1'000;
    for (auto i = 0; i < 100; ++i) {
      const auto x = RandomUtils::get_int(min, max);
      CHECK(x >= min);
      CHECK(x <= max);
    }
  }
}

TEST_CASE("RandomUtils::get_rand", "[RandomUtils]") {
  CHECK_NOTHROW(RandomUtils::get_rand<short>());
  CHECK_NOTHROW(RandomUtils::get_rand<int>());
  CHECK_NOTHROW(RandomUtils::get_rand<long>());
  CHECK_NOTHROW(RandomUtils::get_rand<unsigned>());
  CHECK_NOTHROW(RandomUtils::get_rand<float>());
  CHECK_NOTHROW(RandomUtils::get_rand<double>());
}

TEST_CASE("RandomUtils::get_bool", "[RandomUtils]") {
  std::array<bool, 1'000> values{};
  for (auto& value : values) {
    value = RandomUtils::get_bool();
  }

  auto false_count = 0;
  auto true_count = 0;

  for (const auto value : values) {
    if (value) {
      ++true_count;
    } else {
      ++false_count;
    }
  }

  const auto half = values.size() / 2.0;
  const auto tenth = values.size() / 2.0;

  CHECK(std::abs(true_count - half) < tenth);
  CHECK(std::abs(false_count - half) < tenth);
}