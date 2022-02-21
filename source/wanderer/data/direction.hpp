#pragma once

#include "wanderer/common.hpp"

namespace wanderer {

inline constexpr uint32 direction_up_bit = 1u << 0u;
inline constexpr uint32 direction_down_bit = 1u << 1u;
inline constexpr uint32 direction_right_bit = 1u << 2u;
inline constexpr uint32 direction_left_bit = 1u << 3u;

inline constexpr uint32 direction_up_and_down = direction_up_bit | direction_down_bit;
inline constexpr uint32 direction_left_and_right = direction_left_bit |  //
                                                   direction_right_bit;

}  // namespace wanderer