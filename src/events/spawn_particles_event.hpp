#pragma once

#include <centurion.hpp>  // color

#include "float2.hpp"

namespace wanderer::event {

struct spawn_particles final
{
  float2 position;
  int count{};
  float duration{25};
  cen::color color;
};

}  // namespace wanderer::event