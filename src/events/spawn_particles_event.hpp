#pragma once

#include <centurion.hpp>  // color

#include "core/aliases/float2.hpp"

namespace wanderer {

/// \brief Emitted when a group of particles should be spawned.
/// \ingroup events
struct spawn_particles_event final
{
  float2 position;     ///< The initial position of the particles.
  int count{};         ///< The amount of particles to spawn.
  float duration{25};  ///< The lifetime duration of the particles.
  cen::color color;    ///< The color of the particles.
};

}  // namespace wanderer