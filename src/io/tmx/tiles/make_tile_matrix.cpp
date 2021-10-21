#include "make_tile_matrix.hpp"

#include <vector>  // vector

#include "core/game_constants.hpp"

namespace wanderer::io {

auto make_tile_matrix(const int nRows, const int nCols) -> comp::TileLayer::tile_matrix
{
  const auto rows = static_cast<usize>(nRows);
  const auto cols = static_cast<usize>(nCols);
  return {rows, std::vector<TileID>(cols, glob::empty_tile)};
}

}  // namespace wanderer::io
