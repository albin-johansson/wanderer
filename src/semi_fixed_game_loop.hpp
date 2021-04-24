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

/**
 * \brief Represents a "semi-fixed" game loop, that strives to use a fixed delta, but it
 * can be adjusted dynamically for a few frames.
 *
 * \details This class is designed to be inherited by an "engine" class. The derived
 * classes of this class must provide two functions:
 * \code{cpp}
 *   bool update_input();
 *   void update_logic(delta_time dt);
 * \endcode
 * Where `update_input` should return `true` if the game should continue running; `false`
 * otherwise.
 *
 * \details The game loop will use a tick rate that depends on the refresh rate of the
 * current monitor, but the tick rate is limited to be at most 120, i.e. at most 120
 * updates per second is supported.
 *
 * \tparam T the type of the derived type for CRTP use.
 */
template <typename T>
class semi_fixed_game_loop
{
 public:
  using precision_type = double;
  using seconds_type = cen::seconds<precision_type>;

  /**
   * \brief Creates a game loop instance.
   */
  semi_fixed_game_loop()
      : m_currentTime{cen::counter::now_in_seconds<precision_type>()}
      , m_tickRate{tick_rate<precision_type>()}
      , m_fixedDelta{1.0 / m_tickRate}
  {
    CENTURION_LOG_INFO("Game loop tick rate: %f", m_tickRate);
    CENTURION_LOG_INFO("Game loop fixed delta: %f", m_fixedDelta);
  }

  /**
   * \brief Fetches and updates the stored current time.
   */
  void fetch_current_time() noexcept
  {
    m_currentTime = cen::counter::now_in_seconds<precision_type>();
  }

  /**
   * \brief Updates the state of the game loop.
   */
  void tick()
  {
    const auto newTime = cen::counter::now_in_seconds<precision_type>();
    auto frameTime = newTime - m_currentTime;

    m_currentTime = newTime;
    auto nSteps = 0;

    while (frameTime > seconds_type::zero())
    {
      if (nSteps > m_maxSteps)
      {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = engine()->update_input();
      if (!m_running)
      {
        break;
      }

      const auto deltaTime = std::min(frameTime, m_fixedDelta);
      const delta_time delta{static_cast<delta_time::value_type>(deltaTime.count())};
      engine()->update_logic(delta);

      frameTime -= deltaTime;

      ++nSteps;
    }
  }

  /**
   * \brief Indicates whether or not the game loop is running.
   *
   * \return `true` if the game loop is running; `false` otherwise.
   */
  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  inline constexpr static int m_maxSteps = 5;  ///< Used for avoiding spiral-of-death.

  seconds_type m_currentTime;  ///< The current time value.
  precision_type m_tickRate;   ///< The tick rate, i.e. amount of updates per second.
  seconds_type m_fixedDelta;   ///< The ideal delta value.
  bool m_running{true};

  [[nodiscard]] auto engine() noexcept -> T*
  {
    return static_cast<T*>(this);
  }
};

}  // namespace wanderer
