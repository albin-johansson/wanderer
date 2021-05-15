#pragma once

#include "core/aliases/ints.hpp"
#include "core/aliases/milliseconds.hpp"

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
  i32 frame{0};        ///< Current frame index.
  i32 frame_count{1};  ///< Amount of frames in the animation.
  ms_t then{0};        ///< Time of the previous update of the animation.
  ms_t delay{100};     ///< Duration of each frame in the animation
};

void serialize(auto& archive, animated& a, u32 version)
{
  archive(a.frame, a.frame_count, a.then, a.delay);
}

}  // namespace wanderer::comp
