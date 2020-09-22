#pragma once

#include <string>       // string
#include <type_traits>  // is_same_v, is_convertible_v

#include "step_color.hpp"

namespace step::detail {

template <typename T>
[[nodiscard]] constexpr auto valid_property_type() noexcept -> bool
{
  return std::is_same_v<T, bool> || std::is_same_v<T, int> ||
         std::is_same_v<T, float> || std::is_same_v<T, color> ||
         std::is_same_v<T, file> || std::is_convertible_v<T, std::string>;
}

}  // namespace step::detail
