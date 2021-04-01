#pragma once

#include "map_id.hpp"

namespace wanderer::event {

struct switch_map final
{
  map_id map;
};

}  // namespace wanderer::event
