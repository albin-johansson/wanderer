#include "parse_tile_objects.hpp"

#include <rune/everything.hpp>  // index_to_matrix

#include "core/game_constants.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/physics/hitbox_system.hpp"

namespace wanderer::io {
namespace {

void parse_tile_object(ir::level& data,
                       const TileID tileId,
                       const int tileIndex,
                       const int layerIndex)
{
  const auto tile = find_tile(data.tilesets, tileId).value();

  auto& tileObjectData = data.tile_objects.emplace_back();
  tileObjectData.tile = tile.id;

  const auto [row, col] = rune::index_to_matrix(tileIndex, data.col_count);
  const auto x =
      static_cast<float>(col) * (static_cast<float>(data.tile_width) * data.x_ratio);
  const auto y =
      static_cast<float>(row) * (static_cast<float>(data.tile_height) * data.y_ratio);
  const cen::fpoint position{x, y};

  tileObjectData.drawable =
      make_depth_drawable(tile, position, glob::tile_size<cen::farea>, layerIndex);

  if (const auto& fancy = tile.fancy) {
    tileObjectData.drawable.depth = fancy->depth;
    if (fancy->hitbox) {
      tileObjectData.hitbox = sys::WithPosition(*fancy->hitbox, to_vector(position));
    }
  }
}

}  // namespace

void parse_tile_objects(ir::level& data, const tile_data& tiles, const int layerIndex)
{
  int index = 0;
  for (const auto gid : tiles) {
    const auto id = TileID{gid.get()};

    if (!is_empty(id)) {
      parse_tile_object(data, id, index, layerIndex);
    }

    ++index;
  }
}

}  // namespace wanderer::io
