#pragma once

#include "core/aliases/map_id.hpp"

namespace wanderer::event {

struct level_faded_in final
{
  map_id map;
  float width;
  float height;
  float xStepSize;
  float yStepSize;
};

struct level_faded_out final
{};

}  // namespace wanderer::event
