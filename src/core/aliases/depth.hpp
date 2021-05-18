#pragma once

#include <nenya.hpp>  // strong_type

#include "core/aliases/ints.hpp"

namespace wanderer {
namespace detail {
struct depth_tag_t;
}

using depth_t = nenya::strong_type<int32, detail::depth_tag_t>;

[[nodiscard]] constexpr auto operator"" _depth(const ulonglong d) noexcept -> depth_t
{
  return depth_t{static_cast<depth_t::value_type>(d)};
}

}  // namespace wanderer
