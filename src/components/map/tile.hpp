#pragma once

#include <centurion.hpp>  // irect

#include "core/aliases/depth.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/texture_index.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_entity_t;
}

/**
 * \struct tile
 *
 * \brief Represents a tile in a tileset.
 *
 * \details The `tile` struct represents a tile in a tileset. However, this
 * struct does not represent an actual tile object though, for efficiency
 * reasons.
 *
 * \headerfile tile.hpp
 */
struct tile final
{
  using entity = entity_type<detail::tile_entity_t>;

  tile_id id{glob::empty_tile};  ///< Unique ID associated with the tile.
  texture_index texture;         ///< Associated texture index.
  cen::irect src;                ///< Region in associated tileset.
  depth_t depth{5};              ///< Rendering depth heuristic.
};

void serialize(auto& archive, tile& t, u32 version)
{
  archive(t.id, t.texture, t.src, t.depth);
}

}  // namespace wanderer::comp
