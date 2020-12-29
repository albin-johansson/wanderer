#pragma once

#include <named_type.hpp>

#include "ints.hpp"

namespace wanderer {
namespace detail {
struct tile_id_t;
}

using tile_id = fluent::NamedType<u32,
                                  detail::tile_id_t,
                                  fluent::Comparable,
                                  fluent::Hashable,
                                  fluent::Addable,
                                  fluent::PreIncrementable>;

namespace glob {
inline constexpr tile_id emptyTile{0};
}

[[nodiscard]] inline auto is_empty(const tile_id id) noexcept -> bool
{
  return id == glob::emptyTile;
}

}  // namespace wanderer
