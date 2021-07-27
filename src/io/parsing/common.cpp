#include "common.hpp"

namespace wanderer::io {

auto find_tile(const std::vector<ir::tileset>& tilesets, const tile_id id)
    -> maybe<ir::tile>
{
  for (const auto& tileset : tilesets)
  {
    if (const auto it = tileset.tiles.find(id); it != tileset.tiles.end())
    {
      return it->second;
    }
  }

  return std::nullopt;
}

auto get_tileset_offset(const ir::level& data, const std::string_view tileset) -> int
{
  int offset = 0;

  for (const auto& ts : data.tilesets)
  {
    if (ts.name == tileset)
    {
      break;
    }
    else
    {
      offset += cen::isize(ts.tiles) + 1;
    }
  }

  return offset;
}

auto make_depth_drawable(const ir::tile& tile,
                         const cen::fpoint& pos,
                         const cen::farea& size,
                         const int layer) -> ir::depth_drawable
{
  ir::depth_drawable drawable;

  drawable.texture = tile.texture;
  drawable.src = tile.source;
  drawable.dst = {pos, size};
  drawable.layer = layer;

  return drawable;
}

}  // namespace wanderer::io
