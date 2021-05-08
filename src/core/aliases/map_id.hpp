#pragma once

#include <nenya.hpp>  // strong_type

#include "core/aliases/ints.hpp"

namespace wanderer {
namespace detail {
struct map_id_t;
}

using map_id = nenya::strong_type<i32, detail::map_id_t>;

}  // namespace wanderer
