#pragma once

#include "common/float2.hpp"
#include "common/maybe.hpp"

namespace wanderer::comp {

struct roam final
{
  maybe<float2> destination;
  float cooldown{};
  float cooldown_duration{};
};

}  // namespace wanderer::comp
