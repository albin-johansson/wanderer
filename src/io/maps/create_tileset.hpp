#pragma once

#include <rune/rune.hpp>
#include <tactile-io/ir.hpp>

#include "components/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

[[nodiscard]] auto GetTextureId(const Tactile::IO::Tileset& irTileset) -> uint32;

[[nodiscard]] auto GetTilesetTileSizeRatio(const Tactile::IO::Tileset& irTileset) -> Vec2;

void LoadTilesetTextures(const Tactile::IO::Map& irMap, GraphicsContext& graphics);

void CreateTileset(const Tactile::IO::Map& irMap,
                   Level& level,
                   GraphicsContext& graphics);

}  // namespace wanderer
