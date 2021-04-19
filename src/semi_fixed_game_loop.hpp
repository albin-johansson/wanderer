#pragma once

#include <algorithm>      // min
#include <centurion.hpp>  // ...
#include <concepts>       // floating_point

#include "core/aliases/delta_time.hpp"

namespace wanderer {

template <std::floating_point T>
[[nodiscard]] auto tick_rate() -> T
{
  return std::min(static_cast<T>(120.0),
                  static_cast<T>(cen::screen::refresh_rate().value()));
}

template <typename T>
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

  void fetch_current_time() noexcept
  {
    m_currentTime = cen::counter::now_sec<precision_type>();
  }

  void tick()
  {
    const auto newTime = cen::counter::now_sec<precision_type>();
    auto frameTime = newTime - m_currentTime;
    m_currentTime = newTime;

    auto* engine = derived();
    int nSteps{0};

    while (frameTime > seconds_type::zero())
    {
      if (nSteps > m_maxSteps)
      {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = engine->update_input();
      if (!m_running)
      {
        break;
      }

      const auto deltaTime = std::min(frameTime, m_fixedDelta);
      const delta_time delta{static_cast<delta_time::value_type>(deltaTime.count())};
      engine->update_logic(delta);

      frameTime -= deltaTime;

      ++nSteps;
    }
  }

  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  inline constexpr static int m_maxSteps = 5;

  seconds_type m_currentTime;
  precision_type m_tickRate;
  seconds_type m_fixedDelta;
  bool m_running{true};

  [[nodiscard]] auto derived() noexcept -> T*
  {
    return static_cast<T*>(this);
  }
};

}  // namespace wanderer
