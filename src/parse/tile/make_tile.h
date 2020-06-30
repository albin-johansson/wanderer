#pragma once

#include <rect.h>
#include <step.h>
#include <texture.h>

#include <memory>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

void parse_special_tile(entt::registry& registry,
                        component::Tile::entity tileEntity,
                        const step::Tile& stepTile,
                        TileID firstGID);

[[nodiscard]] auto make_basic_tile(entt::registry& registry,
                                   const TileID id,
                                   const entt::handle<ctn::Texture>& sheet,
                                   const ctn::IRect& src) noexcept
    -> component::Tile::entity;

}  // namespace wanderer
