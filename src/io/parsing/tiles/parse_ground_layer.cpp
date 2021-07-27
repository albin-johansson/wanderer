#include "parse_ground_layer.hpp"

#include <cassert>  // assert
#include <variant>  // get

#include "io/parsing/common.hpp"
#include "io/parsing/tiles/make_tile_matrix.hpp"

namespace wanderer::io {

auto parse_ground_layer(const rune::tmx_tile_layer& tileLayer,
                        const int nRows,
                        const int nCols,
                        const int layerIndex) -> comp::tile_layer
{
  assert(tileLayer.data);

  comp::tile_layer layer;
  layer.matrix = make_tile_matrix(nRows, nCols);
  layer.z = layerIndex;

  int index = 0;
  for (const auto gid : std::get<tile_data>(tileLayer.data->tile_data))
  {
    const auto [row, col] = rune::index_to_matrix<usize>(index, nCols);

    assert(row < layer.matrix.size());
    assert(col < layer.matrix.at(0).size());
    layer.matrix[row][col] = tile_id{gid.get()};

    ++index;
  }

  return layer;
}

}  // namespace wanderer::io
