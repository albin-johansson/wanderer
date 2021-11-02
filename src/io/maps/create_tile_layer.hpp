#pragma once

#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

void CreateTileLayer(const Tactile::IO::Map& irMap,
                     const Tactile::IO::Layer& irLayer,
                     Level& level,
                     int32 layerIndex);

}  // namespace wanderer