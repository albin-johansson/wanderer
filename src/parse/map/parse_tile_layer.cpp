#include "parse_tile_layer.hpp"

#include <vector>  // vector

#include "add_tile_objects.hpp"
#include "index_to_matrix.hpp"
#include "tile_layer.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_tile_matrix(const int nRows, const int nCols)
    -> comp::tile_layer::tile_matrix
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<tile_id>(cols, glob::emptyTile)};
}

void add_ground_layer(entt::registry& registry,
                      const step::tile_layer& tileLayer,
                      const int numRows,
                      const int numColumns,
                      const int layerIndex)
{
  const comp::tile_layer::entity entity{registry.create()};

  auto& layer = registry.emplace<comp::tile_layer>(entity);
  layer.matrix = make_tile_matrix(numRows, numColumns);
  layer.z = layerIndex;

  int index{0};
  for (const auto gid : tileLayer.data()->as_gid()) {
    const auto [row, col] = index_to_matrix<std::size_t>(index, numColumns);
    layer.matrix.at(row).at(col) = tile_id{gid.get()};
    ++index;
  }
}

}  // namespace

void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties,
                      const int index)
{
  assert(properties);
  assert(properties->has("ground"));
  assert(properties->get("ground").is<bool>());

  if (properties->is("ground", true)) {
    add_ground_layer(registry, layer, tilemap.rows, tilemap.cols, index);
  } else {
    if (const auto* data = layer.data()) {
      const auto& tileset = registry.get<comp::tileset>(tilemap.tileset);
      add_tile_objects(registry, tilemap, tileset, data->as_gid(), index);
    }
  }
}

}  // namespace wanderer
