#pragma once

#include <abby.hpp>
#include <cen/area.hpp>
#include <cen/point.hpp>

#include "vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] constexpr auto abby_vector(
    const basic_vector2<T>& vector) noexcept -> abby::vec2<T>
{
  return abby::vec2<T>{vector.x(), vector.y()};
}

template <typename T>
[[nodiscard]] constexpr auto abby_vector(
    const cen::basic_point<T>& point) noexcept -> abby::vec2<T>
{
  return abby::vec2<T>{point.x(), point.y()};
}

template <typename T>
[[nodiscard]] constexpr auto abby_vector(
    const cen::basic_area<T>& area) noexcept -> abby::vec2<T>
{
  return abby::vec2<T>{area.width, area.height};
}

template <typename T>
[[nodiscard]] constexpr auto to_vector(const abby::vec2<T>& vector) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{vector.x, vector.y};
}

}  // namespace wanderer
