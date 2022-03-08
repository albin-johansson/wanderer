#pragma once

#include "wanderer/common.hpp"
#include "wanderer/data/direction.hpp"

namespace wanderer {

struct MovePlayerEvent final
{
  uint32 direction_mask{};
};

struct StopPlayerEvent final
{
  uint32 direction_mask{};
};

}  // namespace wanderer