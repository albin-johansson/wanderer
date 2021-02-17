#pragma once

#include "milliseconds.hpp"

namespace wanderer::comp {

struct particle final
{
  float x;        ///< X-coordinate.
  float y;        ///< Y-coordinate.
  float z;        ///< Z-coordinate.
  float dx;       ///< X-axis acceleration.
  float dy;       ///< Y-axis acceleration.
  float dz;       ///< Z-axis acceleration.
  ms_t start;     ///< Time at the start of the effect.
  ms_t duration;  ///< Lifetime duration.
};

template <typename Archive>
void serialize(Archive& archive, particle& p)
{
  archive(p.x, p.y, p.z, p.dx, p.dy, p.dz, p.start, p.duration);
}

}  // namespace wanderer::comp
