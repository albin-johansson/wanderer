#pragma once

#include <named_type.hpp>

namespace wanderer {

using depth_t = fluent::NamedType<int, struct depth_tag_t, fluent::Comparable>;

[[nodiscard]] constexpr auto operator"" _depth(unsigned long long d) noexcept
    -> depth_t
{
  return depth_t{static_cast<int>(d)};
}

}  // namespace wanderer
