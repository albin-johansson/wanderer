#pragma once

#include "wanderer/core/vocabulary.hpp"

namespace wanderer {

struct LoopState final {
  float64 rate {};               ///< Refresh rate (in Hz).
  float64 fixed_dt {};           ///< Fixed delta time.
  float64 last_update {};        ///< Time of last update.
  float64 frequency {};          ///< The frequency of the system counter.
  int32 max_ticks_per_frame {};  ///< Maximum amount of ticks per frame.
};

class GameLoop {
 public:
  GameLoop();

  virtual ~GameLoop() noexcept = default;

  void start();
  void stop();

  virtual void process_events() = 0;
  virtual void update(float32 dt) = 0;
  virtual void render() = 0;

 private:
  LoopState mState;
  bool mRunning : 1 {false};

  [[nodiscard]] auto now() const -> float64;
};

}  // namespace wanderer
