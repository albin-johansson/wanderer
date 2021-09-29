#pragma once

#include "common/ints.hpp"
#include "common/milliseconds.hpp"

namespace wanderer::comp {

/**
 * \struct animated
 *
 * \brief Represents a general animation.
 *
 * \ingroup components
 *
 * \headerfile animated.hpp
 */
struct animated final
{
  uint64 frame{0};        ///< Current frame index.
  uint64 frame_count{1};  ///< Amount of frames in the animation.
  ms_t then{0};           ///< Time of the previous update of the animation.
  ms_t delay{100};        ///< Duration of each frame in the animation
};

}  // namespace wanderer::comp
