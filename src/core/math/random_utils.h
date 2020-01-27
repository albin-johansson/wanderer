#pragma once
#include <cstdint>
#include <random>
#include <type_traits>
#include <limits>
#include "timer.h"

namespace albinjohansson::wanderer {

/**
 * The RandomUtils class provides utilities related to randomness.
 *
 * @since 0.1.0
 */
class RandomUtils final {
 public:
  RandomUtils() = delete;

  ~RandomUtils() = default;

  /**
   * Returns a random floating-point or integral value.
   *
   * @tparam T the type of returned value, int by default. Must be an integral or floating-point
   * type.
   * @return a random floating-point or integral value.
   * @since 0.1.0
   */
  template<typename T = int>
  [[nodiscard]] static T get_rand() noexcept {
    static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

    std::ranlux24_base rnd(centurion::Timer::high_res());
    return static_cast<T>(rnd());
  }

  /**
   * Returns a random integer in the specified interval. The generated value will be in the range
   * [min, max].
   *
   * @param min the smallest possible value.
   * @param max the largest possible value.
   * @tparam the type of the random value, int by default. Must be an integral or floating-point
   * type.
   * @return a random integer in the specified interval.
   * @since 0.1.0
   */
  template<typename T = int>
  [[nodiscard]] static int get_int(T min, T max) noexcept {
    static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

    std::ranlux24_base rnd(centurion::Timer::high_res());
    return static_cast<T>((rnd() % (max + 1 - min)) + min);
  }

  /**
   * Returns a random bool value.
   *
   * @return a random bool value.
   * @since 0.1.0
   */
  [[nodiscard]]
  static bool get_bool();
};

}
