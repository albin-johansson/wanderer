#pragma once

#include <centurion.hpp>  // basic_point, basic_area

#include "core/math/vector2.hpp"

namespace wanderer {

/// \name Centurion utilities
/// \{

/**
 * \brief Converts a two-dimensional vector to a Centurion point.
 *
 * \ingroup core
 *
 * \tparam T the precision type of the vector.
 *
 * \param vector the vector that will be converted
 *
 * \return a corresponding Centurion point.
 */
template <typename T>
[[nodiscard]] constexpr auto to_point(const basic_vector2<T> vector) noexcept
    -> cen::basic_point<T>
{
  return cen::basic_point<T>{vector.x, vector.y};
}

/**
 * \brief Converts a Centurion point to a two-dimensional vector.
 *
 * \ingroup core
 *
 * \tparam T the precision type of the point.
 *
 * \param point the point that will be converted.
 *
 * \return a corresponding vector.
 */
template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_point<T> point) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{point.x(), point.y()};
}

/**
 * \brief Converts a Centurion area to a two-dimensional vector.
 *
 * \ingroup core
 *
 * \tparam T the precision type of the point.
 *
 * \param area the area that will be converted.
 *
 * \return a corresponding vector.
 */
template <typename T>
[[nodiscard]] constexpr auto to_vector(const cen::basic_area<T> area) noexcept
    -> basic_vector2<T>
{
  return basic_vector2<T>{area.width, area.height};
}

/// \} End of centurion utilities

}  // namespace wanderer
