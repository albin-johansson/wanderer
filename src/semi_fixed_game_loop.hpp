#pragma once

#include <algorithm>        // min
#include <cen/counter.hpp>  // now_sec
#include <cen/screen.hpp>   // refresh_rate
#include <cen/time.hpp>     // seconds

#include "delta.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] auto tick_rate() -> T
{
  return std::min<T>(120.0, static_cast<T>(cen::screen::refresh_rate()));
}

class semi_fixed_game_loop
{
 public:
  using precision_type = double;
  using seconds_type = cen::seconds<precision_type>;

  semi_fixed_game_loop()
      : m_currentTime{cen::counter::now_sec<precision_type>()}
      , m_tickRate{tick_rate<precision_type>()}
      , m_fixedDelta{1.0 / m_tickRate}
  {}

  virtual ~semi_fixed_game_loop() noexcept = default;

  void fetch_current_time() noexcept
  {
    m_currentTime = cen::counter::now_sec<precision_type>();
  }

  void tick()
  {
    const auto newTime = cen::counter::now_sec<precision_type>();
    auto frameTime = newTime - m_currentTime;
    m_currentTime = newTime;

    int nSteps{0};
    while (frameTime > seconds_type::zero()) {
      if (nSteps > m_maxSteps) {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = update_input();
      if (!m_running) {
        break;
      }

      const auto deltaTime = std::min(frameTime, m_fixedDelta);
      update_logic(
          delta_t{static_cast<delta_t::value_type>(deltaTime.count())});

      frameTime -= deltaTime;

      ++nSteps;
    }
  }

  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 protected:
  virtual auto update_input() -> bool
  {
    return true;
  }

  virtual void update_logic(delta_t dt)
  {}

 private:
  constexpr inline static int m_maxSteps = 5;

  seconds_type m_currentTime;
  precision_type m_tickRate;
  seconds_type m_fixedDelta;
  bool m_running{true};
};

}  // namespace wanderer
