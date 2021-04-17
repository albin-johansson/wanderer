#pragma once

#include "core/aliases/map_id.hpp"

namespace wanderer {

struct level_faded_in_event final
{
  map_id map;
  float width;
  float height;
  float xStepSize;
  float yStepSize;
};

struct level_faded_out_event final
{};

}  // namespace wanderer
