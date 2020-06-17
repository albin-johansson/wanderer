#pragma once
#include "game.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class GameLoop final {
 public:
  GameLoop() noexcept;

  void update(Game& game);

  [[nodiscard]] float alpha() const
  {
    float alpha = m_accumulator / m_timeStep;
    if (alpha > 1.0f) {
      alpha = 1.0f;
    }
    return alpha;
  }

 private:
  u64 m_now;
  u64 m_then;
  float m_delta{0};
  float m_accumulator{0};
  float m_deltaBuffer{0};
  const float m_vsyncRate;
  const float m_timeStep;
  const float m_counterFreq;

  /**
   * Returns the maximum allowed frame time (delta time) in seconds. This is
   * used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr float max_frame_time() noexcept { return 0.25f; }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
