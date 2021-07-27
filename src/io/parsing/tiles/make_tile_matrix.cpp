#include "make_tile_matrix.hpp"

#include <vector>  // vector

#include "core/game_constants.hpp"

namespace wanderer::io {

auto make_tile_matrix(const int nRows, const int nCols) -> comp::tile_layer::tile_matrix
{
  const auto rows = static_cast<usize>(nRows);
  const auto cols = static_cast<usize>(nCols);
  return {rows, std::vector<tile_id>(cols, glob::empty_tile)};
}

}  // namespace wanderer::io
