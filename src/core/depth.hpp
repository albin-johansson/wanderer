#pragma once

#include <named_type.hpp>

namespace wanderer {

using depth = fluent::NamedType<int, struct depth_tag_t, fluent::Comparable>;

}
