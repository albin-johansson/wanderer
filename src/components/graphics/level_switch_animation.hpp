#pragma once

#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"

namespace wanderer::comp {

struct level_switch_animation final
{
  maybe<map_id> map;  ///< Optional ID of target map after animation.
  float speed;        ///< Speed scale factor.
  float width;        ///< Current width of the left and right "bars".
  float height;       ///< Current height of the top- and bottom "bars".
  float xStepSize;    ///< Size of an animation step in the x-axis.
  float yStepSize;    ///< Size of an animation step in the y-axis.
  bool fadingIn;      ///< Indicates whether or not the animation is fading in.
};

}  // namespace wanderer::comp
