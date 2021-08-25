#ifndef RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP
#define RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP

#include <centurion.hpp>  // ...
#include <concepts>       // floating_point, derived_from

#include "../math/max.hpp"
#include "../math/min.hpp"
#include "configuration.hpp"
#include "game.hpp"
#include "rune_error.hpp"

namespace rune {

/// \addtogroup core
/// \{

template <typename Game, typename Graphics>
class engine;

/**
 * \class semi_fixed_game_loop
 *
 * \brief Represents a "semi-fixed" game loop, that strives to use a fixed delta, but it
 * can be adjusted dynamically for a few frames at a time.
 *
 * \details The game loop will use a tick rate that depends on the refresh rate of the
 * current monitor, but the tick rate is limited to be at most `max_tick_rate`, see
 * `tick_rate()` for more information.
 *
 * \tparam Game the game type.
 * \tparam Graphics the graphics context type.
 *
 * \see `tick_rate()`
 * \see `max_tick_rate`
 * \see `engine_max_frames_per_tick`
 *
 * \since 0.1.0
 */
template <typename Game, typename Graphics>
class semi_fixed_game_loop
{
 public:
  using game_type = Game;
  using graphics_type = Graphics;
  using engine_type = engine<game_type, graphics_type>;
  using seconds_type = cen::seconds<double>;

  /**
   * \brief Creates a semi-fixed game loop instance.
   *
   * \details The tick rate is determined by comparing the refresh rate of the primary
   * screen and the maximum tick rate, and selecting the minimum value.
   *
   * \param engine the associated engine instance.
   * \param cfg the configuration that will be used.
   *
   * \since 0.1.0
   */
  explicit semi_fixed_game_loop(engine_type* engine)
      : m_engine{engine}
      , m_rate{rune::min(get_engine_max_tick_rate(),
                         static_cast<double>(cen::screen::refresh_rate().value()))}
      , m_maxFramesPerTick{rune::max(1, get_engine_max_frames_per_tick())}
      , m_delta{1.0 / m_rate}
      , m_current{cen::counter::now_in_seconds<double>()}
  {
    if (!m_engine)
    {
      throw rune_error{"Cannot create semi_fixed_game_loop from null engine!"};
    }

    CENTURION_LOG_DEBUG("[rune::semi_fixed_game_loop] Tick rate: %f", m_rate);
    CENTURION_LOG_DEBUG("[rune::semi_fixed_game_loop] Delta: %f", m_delta);
    CENTURION_LOG_DEBUG("[rune::semi_fixed_game_loop] Max frames per tick: %i",
                        m_maxFramesPerTick);
  }

  void fetch_current_time() noexcept
  {
    m_current = cen::counter::now_in_seconds<double>();
  }

  void tick()
  {
    const auto newTime = cen::counter::now_in_seconds<double>();
    auto frameTime = newTime - m_current;

    m_current = newTime;
    auto nSteps = 0;

    while (frameTime > seconds_type::zero())
    {
      if (nSteps > m_maxFramesPerTick)
      {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = m_engine->update_input();
      if (!m_running)
      {
        break;
      }

      const auto dt = rune::min(frameTime, m_delta);
      m_engine->update_logic(static_cast<float>(dt.count()));

      frameTime -= dt;

      ++nSteps;
    }
  }

  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  engine_type* m_engine{};
  double m_rate;
  int m_maxFramesPerTick;
  seconds_type m_delta;
  seconds_type m_current;
  bool m_running{true};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP
