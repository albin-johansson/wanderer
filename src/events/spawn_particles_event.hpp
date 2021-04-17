#pragma once

#include <centurion.hpp>  // color

#include "core/aliases/float2.hpp"

namespace wanderer {

struct spawn_particles_event final
{
  float2 position;
  int count{};
  float duration{25};
  cen::color color;
};

}  // namespace wanderer