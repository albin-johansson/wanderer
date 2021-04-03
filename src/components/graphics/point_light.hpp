#pragma once

#include "vector2.hpp"

namespace wanderer::comp {

struct point_light final
{
  float2 position;         ///< The world position of the light.
  float size;              ///< Base size of the light.
  float fluctuation;       ///< Fluctuation size in [-fluctuationLimit, fluctuationLimit].
  float fluctuationLimit;  ///< Fluctuation size limit.
};

}  // namespace wanderer::comp
