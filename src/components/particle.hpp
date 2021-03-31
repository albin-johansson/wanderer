#pragma once

#include <centurion.hpp>

#include "float3.hpp"
#include "milliseconds.hpp"

namespace wanderer::comp {

struct particle final
{
  float3 position;
  float3 acceleration;
  int tick;    ///< Current tick index.
  int nTicks;  ///< Number of ticks during lifetime.
  cen::color color;
};

template <typename Archive>
void serialize(Archive& archive, particle& p)
{
  archive(p.position, p.acceleration, p.tick, p.nTicks, p.color);
}

}  // namespace wanderer::comp
