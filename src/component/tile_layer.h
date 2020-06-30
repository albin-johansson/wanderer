#pragma once

#include <named_type.hpp>
#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer {

struct TileLayer final {
  using entity = fluent::
      NamedType<entt::entity, struct TileLayerEntityTag, fluent::Comparable>;
  using TileMatrix = std::vector<std::vector<TileID>>;

  TileMatrix matrix;
  int nRows;
  int nCols;
};

}  // namespace wanderer
