#pragma once

#include <named_type.hpp>

namespace wanderer {
namespace detail {
struct map_id_t;
}

using map_id = fluent::NamedType<int,
                                 detail::map_id_t,
                                 fluent::Comparable,
                                 fluent::Hashable,
                                 fluent::PreIncrementable>;

}  // namespace wanderer
