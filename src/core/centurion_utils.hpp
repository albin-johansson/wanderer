#pragma once

#include <centurion.hpp>
#include <cmath>  // lerp

#include "float2.hpp"
#include "ints.hpp"

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

// TODO Centurion 6
[[nodiscard]] constexpr auto merge(const cen::color& a,
                                   const cen::color& b,
                                   const double bias) noexcept -> cen::color
{
  const auto red =
      std::lerp(static_cast<double>(a.red()), static_cast<double>(b.red()), bias);
  const auto green =
      std::lerp(static_cast<double>(a.green()), static_cast<double>(b.green()), bias);
  const auto blue =
      std::lerp(static_cast<double>(a.blue()), static_cast<double>(b.blue()), bias);
  const auto alpha =
      std::lerp(static_cast<double>(a.alpha()), static_cast<double>(b.alpha()), bias);

  return cen::color{static_cast<u8>(red),
                    static_cast<u8>(green),
                    static_cast<u8>(blue),
                    static_cast<u8>(alpha)};
}

}  // namespace wanderer
