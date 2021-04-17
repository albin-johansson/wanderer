#pragma once

#include "core/aliases/ints.hpp"
#include "core/nenya.hpp"

namespace wanderer {
namespace detail {
struct map_id_t;
}

using map_id = nenya::mirror_type<i32, detail::map_id_t>;

}  // namespace wanderer
