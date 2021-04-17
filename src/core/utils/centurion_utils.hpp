#pragma once

#include <centurion.hpp>  // basic_point, basic_area

#include "core/math/vector2.hpp"

namespace wanderer {

/// \addtogroup core
/// \{

/// Converts a two-dimensional vector to a Centurion point
template <typename T>
[[nodiscard]] constexpr auto to_point(const basic_vector2<T>& vector) noexcept
    -> cen::basic_point<T>
{
  return cen::basic_point<T>{vector.x, vector.y};
}

/// Converts a Centurion point to a two-dimensional vector
template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_point<T>& point) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{point.x(), point.y()};
}

/// Converts a Centurion area to a two-dimensional vector
template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_area<T>& area) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{area.width, area.height};
}

/// \} End of group core

}  // namespace wanderer
