#pragma once

#include <cstddef>  // size_t
#include <named_type.hpp>

namespace wanderer {
namespace detail {
struct texture_index_t;
}

using texture_index = fluent::NamedType<std::size_t,
                                        detail::texture_index_t,
                                        fluent::Comparable,
                                        fluent::FunctionCallable>;

}  // namespace wanderer
