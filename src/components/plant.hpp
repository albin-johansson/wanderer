#pragma once

#include <vector>  // vector

#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {

struct plant final
{
  float current{};  ///< Current growth progress, in the range [0, rate].
  float rate{};     ///< Rate of growth.

  float base_y{};     ///< Baseline y-coordinate.
  int tile_height{};  ///< Tile height in associated tileset.

  usize index{};  ///< Index of the associated tiles that is currently active.
  std::vector<tile_id> tiles;  ///< The associated plant tiles.
  std::vector<tile_id> tall;   ///< "Tall" tiles, i.e. tiles that are two tiles high.
};

void serialize(auto& archive, plant& p)
{
  archive(p.current, p.rate, p.base_y, p.tile_height, p.index, p.tiles, p.tall);
}

}  // namespace wanderer::comp
