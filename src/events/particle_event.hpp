#pragma once

#include <centurion.hpp>

#include "milliseconds.hpp"
#include "vector2.hpp"

namespace wanderer::comp {

struct particle_event final
{
  float2 position;
  cen::color baseColor;
  int count;
  int nTicks;
};

}  // namespace wanderer::comp