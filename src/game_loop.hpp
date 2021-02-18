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

class game_loop final
{
 public:
  using time_precision = double;
  using seconds_type = cen::seconds<time_precision>;

  game_loop()
      : m_currentTime{cen::counter::now_sec<time_precision>()}
      , m_tickRate{tick_rate<time_precision>()}
      , m_fixedDelta{1.0 / m_tickRate}
  {}

  void fetch_current_time() noexcept
  {
    m_currentTime = cen::counter::now_sec<time_precision>();
  }

  template <typename T, typename U>
  void tick(T&& input, U&& logic)
  {
    const auto newTime = cen::counter::now_sec<time_precision>();
    auto frameTime = newTime - m_currentTime;
    m_currentTime = newTime;

    int nSteps{0};
    while (frameTime > seconds_type::zero()) {
      if (nSteps > m_maxSteps) {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = input();
      if (!m_running) {
        break;
      }

      const auto deltaTime = std::min(frameTime, m_fixedDelta);
      logic(delta_t{static_cast<delta_t::value_type>(deltaTime.count())});

      frameTime -= deltaTime;

      ++nSteps;
    }
  }

  [[nodiscard]] auto running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  constexpr inline static int m_maxSteps = 5;

  seconds_type m_currentTime;
  time_precision m_tickRate;
  seconds_type m_fixedDelta;
  bool m_running{true};
};

}  // namespace wanderer
