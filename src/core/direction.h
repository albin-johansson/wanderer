#pragma once
#include "random_utils.h"

namespace wanderer {

/**
 * The Direction enum provides values for 4 different directions: up, right,
 * down and left.
 *
 * @since 0.1.0
 */
enum class Direction { Up, Right, Down, Left };

/**
 * Returns a random direction value.
 *
 * @return a random direction value.
 * @since 0.1.0
 */
[[nodiscard]] inline Direction get_random_direction() noexcept
{
  return static_cast<Direction>(RandomUtils::get_int(0, 3));
}

}  // namespace wanderer