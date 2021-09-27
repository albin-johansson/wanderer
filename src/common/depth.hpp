#pragma once

#include <nenya.hpp>  // strong_type

#include "ints.hpp"

namespace wanderer {

namespace tags {
struct depth_tag;
}  // namespace tags

using depth_t = nenya::strong_type<int32, tags::depth_tag>;

[[nodiscard]] constexpr auto operator"" _depth(const ulonglong d) noexcept -> depth_t
{
  return depth_t{static_cast<depth_t::value_type>(d)};
}

}  // namespace wanderer
