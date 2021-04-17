#pragma once

#include "core/nenya.hpp"

namespace wanderer {
namespace detail {
struct delta_time_tag;
}

using delta_time = nenya::mirror_type<float, detail::delta_time_tag>;

}  // namespace wanderer
