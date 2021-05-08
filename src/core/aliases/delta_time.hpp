#pragma once

#include <nenya.hpp> // strong_type

namespace wanderer {
namespace detail {
struct delta_time_tag;
}

using delta_time = nenya::strong_type<float, detail::delta_time_tag>;

}  // namespace wanderer
