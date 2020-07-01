/**
 * @brief Provides the `GameLoop` class.
 * @file game_loop.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "game.h"
#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @class GameLoop
 * @brief Represents the game loop logic.
 * @details This class is responsible for updating and managing the game loop
 * related logic, such as the delta time, interpolation coefficient, etc.
 *
 * @headerfile game_loop.h
 */
class GameLoop final {
 public:
  /**
   * @brief Creates a `GameLoop` instance.
   */
  GameLoop() noexcept;

  /**
   * @brief Updates the state of the game loop.
   * @param game the game instance that will be updated.
   */
  void update(Game& game);

  /**
   * @brief Returns the current value of the interpolation coefficient.
   * @return an interpolation coefficient (alpha) value, in the range [0, 1].
   */
  [[nodiscard]] auto curr_alpha() const -> alpha
  {
    alpha res{m_accumulator.get() / m_timeStep.get()};
    if (res > alpha{1.0f}) {
      res = alpha{1.0f};
    }
    return res;
  }

 private:
  u64 m_now;
  u64 m_then;
  delta m_delta{0};
  delta m_accumulator{0};
  delta m_deltaBuffer{0};
  const float m_vsyncRate;
  const delta m_timeStep;
  const float m_counterFreq;

  /**
   * @brief Returns the maximum allowed frame time (delta time) in seconds.
   * @details This is used to avoid the "spiral of death" in the game loop.
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto max_frame_time() noexcept -> delta
  {
    return delta{0.25f};
  }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
