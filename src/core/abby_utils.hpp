#pragma once

#include <abby.hpp>

#include "vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] constexpr auto abby_vector(
    const basic_vector2<T>& vector) noexcept -> abby::vec2<T>
{
  return abby::vec2<T>{vector.x(), vector.y()};
}

}  // namespace wanderer
