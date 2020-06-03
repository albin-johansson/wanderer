#pragma once
#include "game.h"
#include "types.h"

namespace wanderer {

class GameLoop final {
 public:
  GameLoop() noexcept;

  void update(Game& game);

  [[nodiscard]] f32 alpha() const
  {
    f32 alpha = m_accumulator / m_timeStep;
    if (alpha > 1.0f) {
      alpha = 1.0f;
    }
    return alpha;
  }

 private:
  u64 m_now;
  u64 m_then;
  f32 m_delta{0};
  f32 m_accumulator{0};
  f32 m_deltaBuffer{0};
  const f32 m_vsyncRate;
  const f32 m_timeStep;
  const f32 m_counterFreq;

  /**
   * Returns the maximum allowed frame time (delta time) in seconds. This is
   * used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  constexpr f32 max_frame_time() noexcept { return 0.25f; }

  void smooth_delta() noexcept;
};

}  // namespace wanderer
