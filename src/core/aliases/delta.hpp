#pragma once

#include "nenya.hpp"

namespace wanderer {
namespace detail {
struct delta_tag_t;
}

using delta_t = nenya::mirror_type<float, detail::delta_tag_t>;

}  // namespace wanderer
