#pragma once

#include "wanderer_std.hpp"

namespace wanderer::comp {

/// \brief A component used by NPC entities that can roam randomly.
/// \ingroup components
struct Roam final
{
  maybe<float2> destination;  ///< Target position to roam to.
  float cooldown{};           ///< The current roam cooldown progress.
  float cooldown_duration{};  ///< The total duration of the cooldown.
};

}  // namespace wanderer::comp
