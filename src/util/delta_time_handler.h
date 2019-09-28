#pragma once
#include <SDL_types.h>
#include <SDL_timer.h>
#include <iostream>

namespace wanderer::util {

/**
 * The DeltaTimeHandler class is primarily responsible for handling delta time calculations.
 *
 * @since 0.1.0
 */
class DeltaTimeHandler final {
 private:
  const int targetIterationTimeMs;

  Uint64 then;
  Uint64 now;

  double delta;
  int nSkips;

 public:
  /**
   * @param targetIterationTime the target duration of each iteration time in milliseconds.
   * @since 0.1.0
   */
  explicit DeltaTimeHandler(int targetIterationTime) noexcept
      : targetIterationTimeMs(targetIterationTime) {
    delta = 0;
    nSkips = 0;
    then = 0;
    now = SDL_GetPerformanceCounter();
  }

  ~DeltaTimeHandler() = default;

  /**
   * Begins a new iteration. This method should be called in the beginning of each iteration of each
   * game loop iteration.
   *
   * @since 0.1.0
   */
  inline void BeginIteration() noexcept {
    then = now;
    now = SDL_GetPerformanceCounter();
    delta = static_cast<double>(now - then) / static_cast<double>(SDL_GetPerformanceFrequency());
  }

  /**
   * Ends a previously started iteration. Invoking this method either (1) causes the loop to sleep
   * for a calculated time period (by blocking the invoking thread) or (2) the loop increments its
   * "skips" property and returns immediately, if there is no time to sleep.
   *
   * @since 0.1.0
   */
  inline void EndIteration() noexcept {
    // TODO check if the value is actually in milliseconds
    auto deltaMillis = static_cast<Uint32>(delta / 1000.0);
    if (deltaMillis <= targetIterationTimeMs) {
      SDL_Delay(targetIterationTimeMs - deltaMillis);
    } else {
      nSkips++;
    }
  }

  /**
   * Decrements the "skips" property by one. This method has no effect if the value of the "skips"
   * property is already zero.
   *
   * @since 0.1.0
   */
  inline void DecrementSkips() noexcept {
    nSkips = (nSkips == 0) ? nSkips : --nSkips;
  }

  /**
   * Returns the value of the latest calculated delta time.
   *
   * @return the value of the latest calculated delta time.
   * @since 0.1.0
   */
  [[nodiscard]] inline double GetDelta() const noexcept {
    return delta;
  }

  /**
   * Returns the current amount of skips that have been accumulated. This value is incremented
   * whenever the EndIteration-method is called and the iteration took more time than the target
   * time. Use the DecreaseSkips-method to decrement this value.
   *
   * @return the current amount of skips.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetSkips() const noexcept {
    return nSkips;
  }
};

}