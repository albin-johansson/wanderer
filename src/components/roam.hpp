#pragma once

#include "core/aliases/float2.hpp"
#include "core/aliases/maybe.hpp"

namespace wanderer::comp {

struct roam final
{
  maybe<float2> destination;
  float cooldown{};
  float cooldownDuration{};
};

}  // namespace wanderer::comp
