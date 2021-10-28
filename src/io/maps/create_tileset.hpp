#pragma once

#include <rune/everything.hpp>
#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

[[nodiscard]] auto GetTextureId(const Tactile::IO::Tileset& irTileset)
    -> rune::texture_id;

[[nodiscard]] auto GetTilesetTileSizeRatio(const Tactile::IO::Tileset& irTileset)
    -> float2;

void LoadTilesetTextures(const Tactile::IO::Map& irMap, GraphicsContext& graphics);

void CreateTileset(const Tactile::IO::Map& irMap,
                   comp::Level& level,
                   GraphicsContext& graphics);

}  // namespace wanderer
