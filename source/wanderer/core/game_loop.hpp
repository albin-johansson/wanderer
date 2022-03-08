#pragma once

#include "wanderer/common.hpp"

namespace wanderer {

struct LoopState final
{
  float64 rate{};               ///< Refresh rate (in Hz).
  float64 fixed_dt{};           ///< Fixed delta time.
  float64 then{};               ///< Time of last update.
  float64 frequency{};          ///< The frequency of the system counter.
  int32 max_ticks_per_frame{};  ///< Maximum amount of ticks per frame.
};

class GameLoop
{
 public:
  GameLoop();

  virtual ~GameLoop() noexcept = default;

  void start();

  void stop();

 protected:
  virtual void process_events() {}

  virtual void update([[maybe_unused]] float32 dt) {}

  virtual void render() {}

 private:
  LoopState _state;
  bool _running{};
};

}  // namespace wanderer
