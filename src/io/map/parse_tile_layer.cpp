#include "parse_tile_layer.hpp"

#include "core/game_constants.hpp"
#include "core/utils/centurion_utils.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer {
namespace {

using tile_data = step::detail::data::gid_data;  // FIXME

[[nodiscard]] auto make_tile_matrix(const int nRows, const int nCols)
    -> comp::tile_layer::tile_matrix
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<tile_id>(cols, glob::empty_tile)};
}

[[nodiscard]] auto make_ground_layer(const step::tile_layer& tileLayer,
                                     const int nRows,
                                     const int nCols,
                                     const int zIndex) -> comp::tile_layer
{
  comp::tile_layer layer;
  layer.matrix = make_tile_matrix(nRows, nCols);
  layer.z = zIndex;

  int index{0};

  assert(tileLayer.data());
  for (const auto gid : tileLayer.data()->as_gid())
  {
    const auto [row, col] = index_to_matrix<std::size_t>(index, nCols);

    const tile_id id{gid.get()};
    layer.matrix.at(row).at(col) = id;

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
  for (const auto& ts : data.tilesets)
  {
    if (const auto it = ts.tiles.find(id); it != ts.tiles.end())
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
  auto& tileObjectData = data.tileObjects.emplace_back();
  tileObjectData.tile = tile.id;

  const auto [row, col] = index_to_matrix(tileIndex, data.nCols);
  const auto x = col * data.tileWidth * data.xRatio;
  const auto y = row * data.tileHeight * data.yRatio;
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
  int tileIndex{0};

  for (const auto gid : tiles)
  {
    const tile_id tileId{gid.get()};

    if (!is_empty(tileId))
    {
      add_tile_object(data, tileId, tileIndex, zIndex);
    }

    ++tileIndex;
  }
}

}  // namespace

void parse_tile_layer(ir::level& data,
                      const step::map& stepMap,
                      const step::tile_layer& stepLayer,
                      const step::properties* layerProperties,
                      const int zIndex)
{
  assert(layerProperties);
  assert(layerProperties->has("ground"));
  assert(layerProperties->get("ground").is<bool>());

  if (layerProperties->is("ground", true))
  {
    data.groundLayers.emplace_back(
        make_ground_layer(stepLayer, stepMap.height(), stepMap.width(), zIndex));
  }
  else if (const auto* layerData = stepLayer.data())
  {
    add_tile_objects(data, layerData->as_gid(), zIndex);
  }
}

}  // namespace wanderer
