#pragma once

#include "wanderer/common.hpp"
#include "wanderer/data/direction.hpp"

namespace wanderer {

struct move_player_event final
{
  uint32 direction_mask{};
};

struct stop_player_event final
{
  uint32 direction_mask{};
};

}  // namespace wanderer