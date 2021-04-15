#pragma once

#include "ints.hpp"
#include "nenya.hpp"

namespace wanderer {
namespace detail {
struct tile_id_t;
}

using tile_id = nenya::mirror_type<u32, detail::tile_id_t>;

namespace glob {
inline constexpr tile_id empty_tile{0};
}

[[nodiscard]] inline auto is_empty(const tile_id id) noexcept -> bool
{
  return id == glob::empty_tile;
}

}  // namespace wanderer
