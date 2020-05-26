#pragma once
#include "game.h"
#include "types.h"

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
  u64 m_then = 0;
  u64 m_now = 0;
  float m_delta = 0;
  float m_vsyncRate = 0;
  float m_timeStep = 0;
  float m_counterFreq = 0;
  float m_accumulator = 0;
  float m_deltaBuffer = 0;

  /**
   * A constant that denotes the maximum allowed frame time (delta time) in
   * seconds. This is used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  static constexpr float maxFrameTime = 0.25f;

  void smooth_delta() noexcept;
};

}  // namespace wanderer
