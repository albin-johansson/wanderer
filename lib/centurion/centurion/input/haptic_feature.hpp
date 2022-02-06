#ifndef CENTURION_INPUT_HAPTIC_FEATURE_HPP_
#define CENTURION_INPUT_HAPTIC_FEATURE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum haptic_feature
 *
 * \brief Provides values that represent all of the haptic features.
 *
 * \since 5.2.0
 */
enum class haptic_feature : uint
{
  constant = SDL_HAPTIC_CONSTANT,
  sine = SDL_HAPTIC_SINE,
  left_right = SDL_HAPTIC_LEFTRIGHT,
  triangle = SDL_HAPTIC_TRIANGLE,
  sawtooth_up = SDL_HAPTIC_SAWTOOTHUP,
  sawtooth_down = SDL_HAPTIC_SAWTOOTHDOWN,
  ramp = SDL_HAPTIC_RAMP,
  spring = SDL_HAPTIC_SPRING,
  damper = SDL_HAPTIC_DAMPER,
  inertia = SDL_HAPTIC_INERTIA,
  friction = SDL_HAPTIC_FRICTION,
  custom = SDL_HAPTIC_CUSTOM,
  gain = SDL_HAPTIC_GAIN,
  autocenter = SDL_HAPTIC_AUTOCENTER,
  status = SDL_HAPTIC_STATUS,
  pause = SDL_HAPTIC_PAUSE
};

/// \name Haptic feature functions
/// \{

[[nodiscard]] constexpr auto to_string(const haptic_feature feature) -> std::string_view
{
  switch (feature) {
    case haptic_feature::constant:
      return "constant";

    case haptic_feature::sine:
      return "sine";

    case haptic_feature::left_right:
      return "left_right";

    case haptic_feature::triangle:
      return "triangle";

    case haptic_feature::sawtooth_up:
      return "sawtooth_up";

    case haptic_feature::sawtooth_down:
      return "sawtooth_down";

    case haptic_feature::ramp:
      return "ramp";

    case haptic_feature::spring:
      return "spring";

    case haptic_feature::damper:
      return "damper";

    case haptic_feature::inertia:
      return "inertia";

    case haptic_feature::friction:
      return "friction";

    case haptic_feature::custom:
      return "custom";

    case haptic_feature::gain:
      return "gain";

    case haptic_feature::autocenter:
      return "autocenter";

    case haptic_feature::status:
      return "status";

    case haptic_feature::pause:
      return "pause";

    default:
      throw exception{"Did not recognize haptic feature!"};
  }
}

inline auto operator<<(std::ostream& stream, const haptic_feature feature) -> std::ostream&
{
  return stream << to_string(feature);
}

/// \} End of haptic feature functions

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_FEATURE_HPP_
