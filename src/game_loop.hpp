#pragma once

#include <algorithm>  // min
#include <cen/counter.hpp>
#include <cen/renderer.hpp>
#include <cen/screen.hpp>
#include <cen/types.hpp>

#include "delta.hpp"

namespace wanderer {

class game_loop final
{
 public:
  void fetch_current_time() noexcept
  {
    m_currentTime = cen::counter::now_sec<double>();
  }

  template <typename T, typename U>
  void tick(T&& input, U&& logic)
  {
    const auto newTime = cen::counter::now_sec<double>();
    auto frameTime = newTime - m_currentTime;
    m_currentTime = newTime;

    int nSteps{0};
    while (frameTime > cen::seconds<double>::zero()) {
      if (nSteps > m_maxSteps) {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = input();
      if (!m_running) {
        break;
      }

      const auto deltaTime = std::min(frameTime, m_fixedDelta);
      logic(delta{deltaTime.count()});

      frameTime -= deltaTime;

      ++nSteps;
    }
  }

  [[nodiscard]] auto running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  constexpr inline static int m_maxSteps{5};

  cen::seconds<double> m_currentTime{cen::counter::now_sec<double>()};
  double m_tickRate{
      std::min(120.0, static_cast<double>(cen::screen::refresh_rate()))};
  cen::seconds<double> m_fixedDelta{1.0 / m_tickRate};
  bool m_running{true};
};

}  // namespace wanderer
