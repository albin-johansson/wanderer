#pragma once

#include "wanderer/common.hpp"

namespace wanderer {

struct loop_state final
{
  float64 rate{};               ///< Refresh rate (in Hz).
  float64 delta{};              ///< Fixed delta time.
  float64 then{};               ///< Time of last update.
  float64 frequency{};          ///< The frequency of the system counter.
  int32 max_ticks_per_frame{};  ///< Maximum amount of ticks per frame.
};

class game_loop
{
 public:
  game_loop();

  virtual ~game_loop() noexcept = default;

  void start();

  void stop();

 protected:
  virtual void process_events() {}

  virtual void update([[maybe_unused]] float32 dt) {}

  virtual void render() {}

 private:
  loop_state _state;
  bool _running{};
};

}  // namespace wanderer
