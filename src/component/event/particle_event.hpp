#pragma once

#include <cen/color.hpp>

#include "milliseconds.hpp"
#include "vector2.hpp"

namespace wanderer::comp {

struct particle_event final
{
  vector2f position;
  cen::color baseColor;
  int count;
  int nTicks;
};

}  // namespace wanderer::comp