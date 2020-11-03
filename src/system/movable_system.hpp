#pragma once

#include <optional>  // optional

#include "component/movable.hpp"
#include "direction.hpp"

namespace wanderer::sys::movable {
namespace detail {

[[nodiscard]] auto get_horizontal_dominant_direction(
    const comp::movable& movable) noexcept -> std::optional<direction>
{
  if (movable.velocity.x() < 0) {
    return direction::left;
  } else if (movable.velocity.x() > 0) {
    return direction::right;
  } else {
    return std::nullopt;
  }
}

[[nodiscard]] auto get_vertical_dominant_direction(
    const comp::movable& movable) noexcept -> std::optional<direction>
{
  if (movable.velocity.y() < 0) {
    return direction::up;
  } else if (movable.velocity.y() > 0) {
    return direction::down;
  } else {
    return std::nullopt;
  }
}

}  // namespace detail

/**
 * \brief Returns the appropriate dominant direction for a movable component.
 *
 * \param movable the movable component that will be used.
 *
 * \return the calculated dominant direction for the movable.
 */
[[nodiscard]] auto calc_dominant_direction(
    const comp::movable& movable) noexcept -> direction
{
  if (const auto h = detail::get_horizontal_dominant_direction(movable); h) {
    return *h;
  }

  if (const auto v = detail::get_vertical_dominant_direction(movable); v) {
    return *v;
  }

  return movable.dominantDirection;
}

}  // namespace wanderer::sys::movable
