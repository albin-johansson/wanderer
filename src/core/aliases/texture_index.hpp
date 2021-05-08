#pragma once

#include <cstddef>    // size_t
#include <nenya.hpp>  // strong_type

namespace wanderer {
namespace detail {
struct texture_index_t;
}

using texture_index = nenya::strong_type<std::size_t, detail::texture_index_t>;

}  // namespace wanderer
