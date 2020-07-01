#pragma once

#include <rect.h>
#include <step.h>
#include <texture.h>

#include <memory>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

void parse_special_tile(entt::registry& registry,
                        comp::Tile::entity tileEntity,
                        const step::Tile& stepTile,
                        tile_id firstGID);

[[nodiscard]] auto make_basic_tile(entt::registry& registry,
                                   const tile_id id,
                                   const entt::handle<ctn::Texture>& sheet,
                                   const ctn::IRect& src) noexcept
    -> comp::Tile::entity;

}  // namespace wanderer
