#ifndef CENTURION_INPUT_HAPTIC_PERIODIC_HPP_
#define CENTURION_INPUT_HAPTIC_PERIODIC_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "haptic_effect.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class haptic_periodic
 *
 * \brief Represents a wave-shaped haptic effect that repeats itself over time.
 *
 * \note See the SDL documentation for `SDL_HapticPeriodic` for detailed documentation.
 *
 * \see SDL_HapticPeriodic
 *
 * \since 5.2.0
 */
class haptic_periodic final : public haptic_effect<haptic_periodic>
{
 public:
  inline constexpr static bool hasDirection = true;
  inline constexpr static bool hasEnvelope = true;
  inline constexpr static bool hasTrigger = true;
  inline constexpr static bool hasDelay = true;

  /**
   * \enum periodic_type
   *
   * \brief Provides values that serve as identifiers for the different kinds of
   * "periodic" haptic effects.
   *
   * \since 5.2.0
   */
  enum periodic_type : uint16 {
    sine = SDL_HAPTIC_SINE,
    left_right = SDL_HAPTIC_LEFTRIGHT,
    triangle = SDL_HAPTIC_TRIANGLE,
    sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
    sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN
  };

  /**
   * \brief Creates a periodic haptic effect.
   *
   * \since 5.2.0
   */
  explicit haptic_periodic(const periodic_type type = sine) noexcept
  {
    m_effect.periodic = {};
    set_type(type);
  }

  /**
   * \brief Sets the type of the effect.
   *
   * \param type the periodic effect type.
   *
   * \since 5.2.0
   */
  void set_type(const periodic_type type) noexcept
  {
    representation().type = to_underlying(type);
  }

  /**
   * \brief Sets the period of the wave.
   *
   * \param period the period duration of the wave.
   *
   * \since 5.2.0
   */
  void set_period(const u16ms period) noexcept(noexcept(period.count()))
  {
    representation().period = period.count();
  }

  /**
   * \brief Sets the magnitude (peak value) of the wave.
   *
   * \note If the supplied magnitude is negative, that is interpreted as an extra phase
   * shift of 180 degrees.
   *
   * \param magnitude the magnitude of the wave, can be negative.
   *
   * \since 5.2.0
   */
  void set_magnitude(const int16 magnitude) noexcept
  {
    representation().magnitude = magnitude;
  }

  /**
   * \brief Sets the mean value of the wave.
   *
   * \param mean the mean value of the wave.
   *
   * \since 5.2.0
   */
  void set_mean(const int16 mean) noexcept { representation().offset = mean; }

  /**
   * \brief Sets the phase shift.
   *
   * \param shift the positive phase shift, interpreted as hundredths of a degree.
   *
   * \since 5.2.0
   */
  void set_phase_shift(const uint16 shift) noexcept { representation().phase = shift; }

  /**
   * \brief Returns the current period of the wave.
   *
   * \return the period of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto period() const -> u16ms { return u16ms{representation().period}; }

  /**
   * \brief Returns the current magnitude (peak value) of the wave.
   *
   * \return the magnitude of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto magnitude() const noexcept -> int16 { return representation().magnitude; }

  /**
   * \brief Returns the current mean value of the wave.
   *
   * \return the mean value of the wave.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto mean() const noexcept -> int16 { return representation().offset; }

  /**
   * \brief Returns the current positive phase shift of the wave.
   *
   * \return the positive phase shift of the wave, in hundredths of a degree.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto phase_shift() const noexcept -> uint16 { return representation().phase; }

  /**
   * \brief Returns the internal representation.
   *
   * \return the internal representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto representation() noexcept -> SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }

  /// \copydoc representation();
  [[nodiscard]] auto representation() const noexcept -> const SDL_HapticPeriodic&
  {
    return m_effect.periodic;
  }
};

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_PERIODIC_HPP_
