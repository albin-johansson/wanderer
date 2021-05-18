#pragma once

#include <nenya.hpp>  // strong_type

#include "core/aliases/ints.hpp"

namespace wanderer {
namespace detail {
struct tile_id_t;
}

using tile_id = nenya::strong_type<uint32, detail::tile_id_t>;

namespace glob {
inline constexpr tile_id empty_tile{0};
}

[[nodiscard]] inline auto is_empty(const tile_id id) noexcept -> bool
{
  return id == glob::empty_tile;
}

}  // namespace wanderer
