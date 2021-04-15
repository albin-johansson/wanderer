#pragma once

#include "ints.hpp"
#include "nenya.hpp"

namespace wanderer {
namespace detail {
struct depth_tag_t;
}

using depth_t = nenya::mirror_type<i32, detail::depth_tag_t>;

[[nodiscard]] constexpr auto operator"" _depth(unsigned long long d) noexcept -> depth_t
{
  return depth_t{static_cast<int>(d)};
}

}  // namespace wanderer
