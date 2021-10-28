#pragma once

#include <rune/rune.hpp>
#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

[[nodiscard]] auto GetTextureId(const Tactile::IO::Tileset& irTileset) -> uint32;

[[nodiscard]] auto GetTilesetTileSizeRatio(const Tactile::IO::Tileset& irTileset)
    -> float2;

void LoadTilesetTextures(const Tactile::IO::Map& irMap, GraphicsContext& graphics);

void CreateTileset(const Tactile::IO::Map& irMap,
                   comp::Level& level,
                   GraphicsContext& graphics);

}  // namespace wanderer
