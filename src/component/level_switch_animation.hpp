#pragma once

#include "map_id.hpp"
#include "maybe.hpp"

namespace wanderer::comp {

struct level_switch_animation final
{
  maybe<map_id> map;  ///< ID of target map after animation.
  int step;           ///< Current step of the animation.
  int nSteps;         ///< The total number of steps of the animation.
  float hStepSize;    ///< Size of a step in the x-axis.
  float vStepSize;    ///< Size of a step in the y-axis.
  bool fadingIn;      ///< Indicates whether or not the animation is fading in.
};

}  // namespace wanderer::comp
