#pragma once

#include <named_type.hpp>

#include "alpha.hpp"
#include "delta.hpp"
#include "game.hpp"
#include "ints.hpp"

namespace wanderer {

/**
 * @class game_loop
 *
 * @brief Represents the game loop logic.
 *
 * @details This class is responsible for updating and managing the game loop
 * related logic, such as the delta time, interpolation coefficient, etc.
 *
 * @headerfile game_loop.hpp
 */
class game_loop final
{
 public:
  /**
   * @brief Creates a `game_loop` instance.
   */
  game_loop() noexcept;

  /**
   * @brief Updates the state of the game loop.
   *
   * @param game the game instance that will be updated.
   */
  void update(game& game);

  /**
   * @brief Returns the current value of the interpolation coefficient.
   *
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
   *
   * @details This is used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  [[nodiscard]] static constexpr auto max_frame_time() noexcept -> delta
  {
    return delta{0.25f};
  }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
