#pragma once

#include <centurion.hpp>  // irect

#include "core/aliases/depth.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/texture_index.hpp"
#include "core/aliases/tile_id.hpp"
#include "core/game_constants.hpp"

namespace wanderer::comp {

namespace tags {
struct tile_tag;
}  // namespace tags

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
  using entity = entity_type<tags::tile_tag>;

  tile_id id{glob::empty_tile};  ///< Unique ID associated with the tile.
  texture_index texture{};       ///< Associated texture index.
  cen::irect src;                ///< Region in associated tileset.
  depth_t depth{5};              ///< Rendering depth heuristic.
};

void serialize(auto& archive, tile& t, uint32 version)
{
  archive(t.id, t.texture, t.src, t.depth);
}

}  // namespace wanderer::comp
