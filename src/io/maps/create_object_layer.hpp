#pragma once

#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

void CreateObjectLayer(const Tactile::IO::Map& irMap,
                       const Tactile::IO::Layer& irLayer,
                       Level& level,
                       GraphicsContext& graphics,
                       float2 ratio);

}  // namespace wanderer
