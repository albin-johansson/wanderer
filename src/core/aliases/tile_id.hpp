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

inline constexpr tile_id g_emptyTile{0};

}  // namespace wanderer
