#pragma once

#include <named_type.hpp>

#include "ints.hpp"

namespace wanderer {
namespace detail {
struct depth_tag_t;
}

using depth_t = fluent::NamedType<i32, detail::depth_tag_t, fluent::Comparable>;

[[nodiscard]] constexpr auto operator"" _depth(unsigned long long d) noexcept -> depth_t
{
  return depth_t{static_cast<int>(d)};
}

}  // namespace wanderer
