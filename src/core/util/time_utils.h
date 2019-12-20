#pragma once
#include <cstdint>

namespace albinjohansson::wanderer {

/**
 * The TimeUtils provides utilities related to timers.
 *
 * @since 0.1.0
 */
class TimeUtils final {
 public:
  TimeUtils() = delete;

  ~TimeUtils() = default;

  /**
   * Returns the amount of milliseconds since the SDL library was initialized.
   *
   * @return the amount of milliseconds since the SDL library was initialized.
   * @since 0.1.0
   */
  [[nodiscard]] static uint64_t GetMillis() noexcept;

  /**
   * Returns the value of the high-resolution counter.
   *
   * @return the value of the high-resolution counter.
   * @since 0.1.0
   */
  [[nodiscard]] static uint64_t GetHighResTime() noexcept;

  /**
   * Returns the frequency of the high-resolution counter.
   *
   * @return the frequency of the high-resolution counter.
   * @since 0.1.0
   */
  [[nodiscard]] static uint64_t GetHighResFreq() noexcept;
};

}
