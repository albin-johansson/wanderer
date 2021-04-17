#pragma once

#include <concepts>  // convertible_to
#include <ranges>    // range

namespace wanderer {

/// \addtogroup core
/// \{

// clang-format off

template <typename T, typename Elem>
concept has_value_type = requires (T t)
{
  typename T::value_type;
  std::convertible_to<typename T::value_type, Elem>;
};

// An iterable container with a value type convertible to the specified element type
template <typename T, typename Elem>
concept container_type = std::ranges::range<T> &&
                         has_value_type<T, Elem>;

// clang-format on

/// \} End of group core

}  // namespace wanderer
