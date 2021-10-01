#pragma once

#include "common/float2.hpp"

namespace wanderer::comp {

/// \brief Represents light sources focused at specific points.
/// \ingroup components
struct point_light final
{
  float2 position;      ///< The world position of the light.
  float size{};         ///< Base size of the light.
  float fluctuation{};  ///< Fluctuation size in [-fluctuation_limit, fluctuation_limit].
  float fluctuation_step{};   ///< Size of each fluctuation increment.
  float fluctuation_limit{};  ///< Fluctuation size limit.
};

}  // namespace wanderer::comp
