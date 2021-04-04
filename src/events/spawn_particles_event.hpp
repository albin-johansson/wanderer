#pragma once

#include <centurion.hpp>

#include "float2.hpp"
#include "milliseconds.hpp"

namespace wanderer::event {

struct spawn_particles final
{
  float2 position;
  cen::color baseColor;
  int count;
  int nTicks;
};

}  // namespace wanderer::event