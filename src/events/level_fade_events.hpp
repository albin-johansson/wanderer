#pragma once

#include "map_id.hpp"

namespace wanderer::event {

struct level_faded_in final
{
  map_id map;
  int step;
  int nSteps;
  float hStepSize;
  float vStepSize;
};

struct level_faded_out final
{};

}  // namespace wanderer::event
