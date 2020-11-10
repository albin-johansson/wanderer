#pragma once

#include <cen/log.hpp>
#include <cen/point.hpp>
#include <cen/rect.hpp>

#include "vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] constexpr auto to_point(const basic_vector2<T>& vector) noexcept
    -> cen::basic_point<T>
{
  return cen::basic_point<T>{vector.x(), vector.y()};
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
