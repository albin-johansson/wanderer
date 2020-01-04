#pragma once
#include <cstdint>

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

  [[nodiscard]]
  static uint64_t get_rand();

  /**
   * Returns a random integer in the specified interval. The generated value will be in the range
   * [min, max].
   *
   * @param min the smallest possible value.
   * @param max the largest possible value.
   * @return a random integer in the specified interval.
   * @since 0.1.0
   */
  [[nodiscard]]
  static int get_int(int min, int max);

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
