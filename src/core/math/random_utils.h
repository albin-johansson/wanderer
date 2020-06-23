#pragma once

#ifndef NDEBUG
#include <log.h>
#endif  // NDEBUG

#include <timer.h>

#include <random>

namespace wanderer::math {
namespace {

inline std::mt19937 random;

}

void init_rnd() noexcept
{
  const auto seed = centurion::Timer::high_res();
#ifndef NDEBUG
  centurion::Log::info("Using seed: %u (for RNG)", seed);
#endif  // NDEBUG
  random.seed(seed);
}

/**
 * Returns a random value in the specified inclusive range.
 *
 * @tparam T the type of the value to be obtained, must be either integral or
 * floating-point.
 * @param min the minimum possible value.
 * @param max the maximum possible value.
 * @return a random integer in the specified range.
 */
template <typename T>
[[nodiscard]] T get_random(T min, T max) noexcept
{
  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist{min, max};
    return dist(random);
  } else {
    std::uniform_int_distribution<T> dist{min, max};
    return dist(random);
  }
}

}  // namespace wanderer::math
