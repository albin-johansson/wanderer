#pragma once

#include <algorithm>    // generate
#include <array>        // array
#include <functional>   // ref
#include <random>       // mt19937, random_device, seed_seq, ...
#include <type_traits>  // is_floating_point_v

namespace wanderer {

using random_engine = std::mt19937;

[[nodiscard]] inline auto get_seeded_engine() -> random_engine
{
  // Based on
  // https://codereview.stackexchange.com/questions/109260/seed-stdmt19937-from-stdrandom-device

  constexpr auto n = random_engine::state_size;

  std::random_device source;
  std::array<std::random_device::result_type, (n - 1) / sizeof(source()) + 1> data{};

  std::generate(data.begin(), data.end(), std::ref(source));
  std::seed_seq seeds(data.begin(), data.end());

  return random_engine(seeds);
}

inline random_engine engine{get_seeded_engine()};

/**
 * \brief Returns a random value in the specified inclusive range.
 *
 * \tparam T the type of the value to be obtained, must be either integral or
 * floating-point.
 *
 * \param min the minimum possible value.
 * \param max the maximum possible value.
 *
 * \return a random value in the specified range.
 */
template <typename T>
[[nodiscard]] auto get_random(const T min, const T max) -> T
{
  if constexpr (std::is_floating_point_v<T>)
  {
    return std::uniform_real_distribution<T>{min, max}(engine);
  }
  else
  {
    return std::uniform_int_distribution<T>{min, max}(engine);
  }
}

/// Returns a random boolean value
[[nodiscard]] inline auto next_bool() -> bool
{
  return get_random(0, 99) < 50;
}

}  // namespace wanderer
