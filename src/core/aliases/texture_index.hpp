#pragma once

#include <cstddef>  // size_t

#include "nenya.hpp"

namespace wanderer {
namespace detail {
struct texture_index_t;
}

using texture_index = nenya::mirror_type<std::size_t, detail::texture_index_t>;

}  // namespace wanderer
