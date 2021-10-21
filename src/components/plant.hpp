#pragma once

#include <vector>  // vector

#include "wanderer_std.hpp"

namespace wanderer::comp {

struct Plant final
{
  float current{};  ///< Current growth progress, in the range [0, rate].
  float rate{};     ///< Rate of growth.

  float base_y{};       ///< Baseline y-coordinate.
  int32 tile_height{};  ///< Tile height in associated tileset.

  usize index{};              ///< Index of the associated tiles that is currently active.
  std::vector<TileID> tiles;  ///< The associated plant tiles.
  std::vector<TileID> tall;   ///< "Tall" tiles, i.e. tiles that are two tiles high.
};

}  // namespace wanderer::comp
