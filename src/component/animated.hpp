/**
 * @brief Provides the `Animated` component.
 * @file animated.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Animated
 * @brief Represents a general animation.
 *
 * @var Animated::frame
 * The current frame index. Starts at 0.
 * @var Animated::nFrames
 * The amount of frames in the animation.
 * @var Animated::then
 * The time of the previous update of the animation, in milliseconds.
 * @var Animated::delay
 * The duration of each frame in the animation, in milliseconds.
 *
 * @headerfile animated.hpp
 */
struct Animated final
{
  u32 frame{0};
  u32 nFrames{1};
  u32 then{0};
  u32 delay{100};
};

}  // namespace wanderer::comp
