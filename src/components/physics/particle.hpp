#pragma once

#include <centurion.hpp>  // color

#include "float3.hpp"

namespace wanderer::comp {

/// \brief Represents a particle, intended to be used for visual effects.
/// \ingroup components
struct particle final
{
  float3 position;      ///< The world position of the particle.
  float3 acceleration;  ///< The acceleration of the particle.
  float now{};          ///< The cumulative amount of time the particle has existed.
  float duration{};     ///< How long the particle will exist.
  cen::color color;     ///< The color of the particle.
};

}  // namespace wanderer::comp
