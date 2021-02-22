#pragma once

#include "map_id.hpp"

namespace wanderer::comp {

struct level_faded_in_event final
{
  map_id map;
  int step;
  int nSteps;
  float hStepSize;
  float vStepSize;
};

struct level_faded_out_event final
{};

}  // namespace wanderer::comp
