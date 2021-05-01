#pragma once

#include <concepts>     // invocable
#include <ranges>       // range
#include <type_traits>  // invoke_result_t

namespace wanderer {

// clang-format off

/// Returns a value accumulated from visiting each element in a range
template <std::ranges::range T, std::invocable<const typename T::value_type&> Callable>
[[nodiscard]] constexpr auto accumulate(const T& range, Callable&& callable)
{
  using value_type = std::invoke_result_t<Callable, typename T::value_type>;

  value_type value{};
  for (const auto& elem : range)
  {
    value += callable(elem);
  }

  return value;
}

// clang-format on

}  // namespace wanderer
