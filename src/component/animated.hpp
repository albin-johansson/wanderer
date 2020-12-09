#pragma once

#include "milliseconds.hpp"

namespace wanderer::comp {

/**
 * \struct animated
 *
 * \brief Represents a general animation.
 *
 * \var animated::frame
 * The current frame index. Starts at 0.
 * \var animated::nFrames
 * The amount of frames in the animation.
 * \var animated::then
 * The time of the previous update of the animation, in milliseconds.
 * \var animated::delay
 * The duration of each frame in the animation, in milliseconds.
 *
 * \headerfile animated.hpp
 */
struct animated final
{
  int frame{0};
  int nFrames{1};
  ms_t then{0};
  ms_t delay{100};
};

}  // namespace wanderer::comp
