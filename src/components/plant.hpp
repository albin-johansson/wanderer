#pragma once

#include <vector>  // vector

#include "core/aliases/ints.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {

struct plant final
{
  float current{};
  float rate{};
  usize index{};
  std::vector<tile_id> tiles;
};

void serialize(auto& archive, plant& p)
{
  archive(p.current, p.rate, p.index, p.tiles);
}

}  // namespace wanderer::comp
