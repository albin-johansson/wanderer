#pragma once

#include <centurion.hpp>

#include "vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] constexpr auto to_point(const basic_vector2<T>& vector) noexcept
    -> cen::basic_point<T>
{
  return cen::basic_point<T>{vector.x, vector.y};
}

template <typename T>
[[nodiscard]] constexpr auto to_vector(
    const cen::basic_point<T>& point) noexcept -> basic_vector2<T>
{
  return basic_vector2<T>{point.x(), point.y()};
}

template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_area<T>& area) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{area.width, area.height};
}

inline void log(const cen::frect& rect) noexcept
{
  cen::log::info("rect: ({%f, %f} {%f x %f})",
                 rect.x(),
                 rect.y(),
                 rect.width(),
                 rect.height());
}

}  // namespace wanderer
