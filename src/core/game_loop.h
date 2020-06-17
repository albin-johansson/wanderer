#pragma once
#include "game.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class GameLoop final {
 public:
  GameLoop() noexcept;

  void update(Game& game);

  [[nodiscard]] Alpha alpha() const
  {
    Alpha alpha{m_accumulator.get() / m_timeStep.get()};
    if (alpha > Alpha{1.0f}) {
      alpha = Alpha{1.0f};
    }
    return alpha;
  }

 private:
  u64 m_now;
  u64 m_then;
  Delta m_delta{0};
  Delta m_accumulator{0};
  Delta m_deltaBuffer{0};
  const float m_vsyncRate;
  const Delta m_timeStep;
  const float m_counterFreq;

  /**
   * Returns the maximum allowed frame time (delta time) in seconds. This is
   * used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr Delta max_frame_time() noexcept
  {
    return Delta{0.25f};
  }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
