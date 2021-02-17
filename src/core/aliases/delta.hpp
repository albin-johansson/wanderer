#pragma once

#include <named_type.hpp>

namespace wanderer {
namespace detail {
struct delta_tag_t;
}

// TODO this is often cast to float, maybe change the underlying type to float?
using delta_t = fluent::NamedType<double,
                                  detail::delta_tag_t,
                                  fluent::Comparable,
                                  fluent::Addable,
                                  fluent::Subtractable,
                                  fluent::Incrementable,
                                  fluent::Decrementable>;

}  // namespace wanderer
