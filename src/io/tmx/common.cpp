#include "common.hpp"

namespace wanderer::io {

auto find_tile(const std::vector<ir::tileset>& tilesets, const tile_id id)
    -> maybe<ir::tile>
{
  for (const auto& tileset : tilesets) {
    if (const auto it = tileset.tiles.find(id); it != tileset.tiles.end()) {
      return it->second;
    }
  }

  return std::nullopt;
}

auto get_tileset_offset(const ir::level& data, const std::string_view tileset) -> int
{
  int offset = 0;

  for (const auto& ts : data.tilesets) {
    if (ts.name == tileset) {
      break;
    }
    else {
      offset += cen::isize(ts.tiles) + 1;
    }
  }

  return offset;
}

auto get_tileset_tile_size(const ir::level& data, const std::string_view tileset)
    -> maybe<cen::iarea>
{
  for (const auto& ts : data.tilesets) {
    if (ts.name == tileset) {
      return cen::iarea{ts.tile_width, ts.tile_height};
    }
  }

  return std::nullopt;
}

auto make_depth_drawable(const ir::tile& tile,
                         const cen::fpoint& pos,
                         const cen::farea& size,
                         const int layer) -> ir::drawable
{
  ir::drawable drawable;

  drawable.texture = tile.texture;
  drawable.src = tile.source;
  drawable.dst = {pos, size};
  drawable.layer = layer;

  return drawable;
}

}  // namespace wanderer::io
