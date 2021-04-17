#pragma once

#include <centurion.hpp>  // basic_point, basic_area
#include <cmath>          // lerp

#include "core/math/vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] constexpr auto to_point(const basic_vector2<T>& vector) noexcept
    -> cen::basic_point<T>
{
  return cen::basic_point<T>{vector.x, vector.y};
}

template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_point<T>& point) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{point.x(), point.y()};
}

template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_area<T>& area) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{area.width, area.height};
}

}  // namespace wanderer
