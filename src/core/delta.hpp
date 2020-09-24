#pragma once

#include <named_type.hpp>

namespace wanderer {

using delta = fluent::NamedType<float,
                                struct delta_tag_t,
                                fluent::Comparable,
                                fluent::Addable,
                                fluent::Subtractable,
                                fluent::Incrementable,
                                fluent::Decrementable>;

}
