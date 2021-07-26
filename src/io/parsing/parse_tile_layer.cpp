#include "parse_tile_layer.hpp"

#include <cassert>   // assert
#include <rune.hpp>  // index_to_matrix

#include "core/aliases/ints.hpp"
#include "core/game_constants.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer {
namespace {

using tile_data = rune::tmx_data::gid_data;

[[nodiscard]] auto make_tile_matrix(const int nRows, const int nCols)
    -> comp::tile_layer::tile_matrix
{
  const auto rows = static_cast<usize>(nRows);
  const auto cols = static_cast<usize>(nCols);
  return {rows, std::vector<tile_id>(cols, glob::empty_tile)};
}

[[nodiscard]] auto make_ground_layer(const rune::tmx_tile_layer& tileLayer,
                                     const int nRows,
                                     const int nCols,
                                     const int zIndex) -> comp::tile_layer
{
  assert(tileLayer.data);

  comp::tile_layer layer;
  layer.matrix = make_tile_matrix(nRows, nCols);
  layer.z = zIndex;

  for (int index = 0; const auto gid : std::get<tile_data>(tileLayer.data->tile_data))
  {
    const auto [row, col] = rune::index_to_matrix<usize>(index, nCols);

    assert(row < layer.matrix.size());
    assert(col < layer.matrix.at(0).size());
    layer.matrix[row][col] = tile_id{gid.get()};

    ++index;
  }

  return layer;
}

[[nodiscard]] auto add_depth_drawable(const ir::tile& tile,
                                      const cen::fpoint& dstPos,
                                      const int zIndex) -> ir::depth_drawable
{
  ir::depth_drawable drawable;

  drawable.texture = tile.texture;
  drawable.src = tile.source;
  drawable.dst = {dstPos, glob::tile_size<cen::farea>};
  drawable.layer = zIndex;

  return drawable;
}

[[nodiscard]] auto find_tile(ir::level& data, const tile_id id) -> maybe<ir::tile>
{
  for (const auto& tileset : data.tilesets)
  {
    if (const auto it = tileset.tiles.find(id); it != tileset.tiles.end())
    {
      return it->second;
    }
  }

  return std::nullopt;
}

void add_tile_object(ir::level& data,
                     const tile_id tileId,
                     const int tileIndex,
                     const int zIndex)
{
  const auto tile = find_tile(data, tileId).value();
  auto& tileObjectData = data.tile_objects.emplace_back();
  tileObjectData.tile = tile.id;

  const auto [row, col] = rune::index_to_matrix(tileIndex, data.col_count);
  const auto x = col * data.tile_width * data.x_ratio;
  const auto y = row * data.tile_height * data.y_ratio;
  const cen::fpoint position{x, y};

  tileObjectData.drawable = add_depth_drawable(tile, position, zIndex);

  if (tile.fancy)
  {
    const auto& fancy = *tile.fancy;
    tileObjectData.drawable.depth = fancy.depth;

    if (fancy.hitbox)
    {
      tileObjectData.hitbox = sys::with_position(*fancy.hitbox, to_vector(position));
    }
  }
}

void add_tile_objects(ir::level& data, const tile_data& tiles, const int zIndex)
{
  for (int index = 0; const auto gid : tiles)
  {
    const auto id = tile_id{gid.get()};

    if (!is_empty(id))
    {
      add_tile_object(data, id, index, zIndex);
    }

    ++index;
  }
}

}  // namespace

void parse_tile_layer(ir::level& data,
                      const rune::tmx_map& map,
                      const rune::tmx_tile_layer& layer,
                      const rune::tmx_properties& properties,
                      const int zIndex)
{
  assert(rune::tmx::is_bool(properties, "ground"));
  if (rune::tmx::get_bool(properties, "ground"))
  {
    data.ground_layers.push_back(make_ground_layer(layer, map.height, map.width, zIndex));
  }
  else if (layer.data)
  {
    add_tile_objects(data, std::get<tile_data>(layer.data->tile_data), zIndex);
  }
}

}  // namespace wanderer
