#pragma once

#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer {

void CreateLayers(const Tactile::IO::Map& irMap,
                  comp::Level& level,
                  GraphicsContext& graphics);

}  // namespace wanderer
