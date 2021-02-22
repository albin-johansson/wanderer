#pragma once

#include <cen/color.hpp>

#include "milliseconds.hpp"

namespace wanderer::comp {

struct particle final
{
  float x;     ///< X-coordinate.
  float y;     ///< Y-coordinate.
  float z;     ///< Z-coordinate.
  float dx;    ///< X-axis acceleration.
  float dy;    ///< Y-axis acceleration.
  float dz;    ///< Z-axis acceleration.
  int tick;    ///< Current tick index.
  int nTicks;  ///< Number of ticks during lifetime.
  cen::color color;
};

template <typename Archive>
void serialize(Archive& archive, particle& p)
{
  archive(p.x, p.y, p.z, p.dx, p.dy, p.dz, p.nTicks);
}

}  // namespace wanderer::comp
