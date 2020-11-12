#pragma once

#include <named_type.hpp>

namespace wanderer {

using depth = fluent::NamedType<int, struct depth_tag_t, fluent::Comparable>;

[[nodiscard]] constexpr auto operator"" _depth(unsigned long long d) noexcept
    -> depth
{
  return depth{static_cast<int>(d)};
}

}  // namespace wanderer
