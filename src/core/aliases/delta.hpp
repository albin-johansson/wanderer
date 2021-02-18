#pragma once

#include <named_type.hpp>

namespace wanderer {
namespace detail {
struct delta_tag_t;
}

using delta_t = fluent::NamedType<float,
                                  detail::delta_tag_t,
                                  fluent::Comparable,
                                  fluent::Addable,
                                  fluent::Subtractable,
                                  fluent::Incrementable,
                                  fluent::Decrementable,
                                  fluent::FunctionCallable>;

}  // namespace wanderer
