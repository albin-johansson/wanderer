#pragma once

#include "ints.hpp"
#include "nenya.hpp"

namespace wanderer {
namespace detail {
struct map_id_t;
}

using map_id = nenya::mirror_type<i32, detail::map_id_t>;

}  // namespace wanderer
