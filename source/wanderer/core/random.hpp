#pragma once

#include <random>       // mt19937, uniform_real_distribution, uniform_int_distribution
#include <type_traits>  // is_floating_point_v

#include "wanderer/common.hpp"

namespace wanderer {

using random_engine = std::mt19937;

/**
 * \brief Creates a seeded pseudo-random number generation engine.
 *
 * \return a seeded random engine.
 */
[[nodiscard]] auto make_random_engine() -> random_engine;

/**
 * \brief Returns a random value in the range [min, max].
 *
 * \param min the minimum possible value.
 * \param max the maximum possible value.
 *
 * \return a random value in the range.
 */
template <typename T>
[[nodiscard]] auto next_random(const T min, const T max) -> T
{
  static auto engine = make_random_engine();

  if constexpr (std::is_floating_point_v<T>) {
    return std::uniform_real_distribution<T>{min, max}(engine);
  }
  else {
    return std::uniform_int_distribution<T>{min, max}(engine);
  }
}

/**
 * \brief Returns a random boolean value.
 *
 * \return a random boolean value.
 */
[[nodiscard]] inline auto next_bool() -> bool
{
  return next_random(0, 100) <= 50;
}

/**
 * \brief Returns a random float in the interval [0, 1].
 *
 * \return a random normalized float.
 */
[[nodiscard]] inline auto next_float() -> float32
{
  return next_random(0.0f, 1.0f);
}

}  // namespace wanderer