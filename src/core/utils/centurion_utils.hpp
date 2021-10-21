#pragma once

#include <concepts>  // floating_point

#include <centurion.hpp>        // basic_point, basic_area
#include <rune/everything.hpp>  // basic_vector2

#include "wanderer_std.hpp"

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
[[nodiscard]] constexpr auto to_point(const float2 vector) noexcept -> cen::fpoint
{
  return cen::fpoint{vector.x, vector.y};
}

[[nodiscard]] constexpr auto to_vector(const cen::fpoint point) noexcept -> float2
{
  return float2{point.x(), point.y()};
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
[[nodiscard]] constexpr auto to_vector(const cen::farea area) noexcept -> float2
{
  return float2{area.width, area.height};
}

[[nodiscard]] constexpr auto to_rune_vector(const float2 vector) noexcept -> float2
{
  return float2{vector.x, vector.y};
}

[[nodiscard]] constexpr auto to_rune_vector(const cen::fpoint point) noexcept
    -> rune::float2
{
  return rune::float2{point.x(), point.y()};
}

[[nodiscard]] constexpr auto to_rune_vector(const cen::farea area) noexcept
    -> rune::float2
{
  return rune::float2{area.width, area.height};
}

/// \} End of centurion utilities

}  // namespace wanderer
