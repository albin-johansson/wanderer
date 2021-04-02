#pragma once

#include <named_type.hpp>

#include "ints.hpp"

namespace wanderer {
namespace detail {
struct map_id_t;
}

using map_id = fluent::NamedType<i32,
                                 detail::map_id_t,
                                 fluent::Comparable,
                                 fluent::Hashable,
                                 fluent::PreIncrementable>;

}  // namespace wanderer
