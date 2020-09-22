#pragma once

#include <memory>
#include <rect.hpp>
#include <step_tile.hpp>
#include <texture.hpp>

#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

void parse_special_tile(entt::registry& registry,
                        comp::Tile::entity tileEntity,
                        const step::tile& stepTile,
                        tile_id firstGID);

[[nodiscard]] auto make_basic_tile(entt::registry& registry,
                                   const tile_id id,
                                   const entt::handle<cen::texture>& sheet,
                                   const cen::irect& src) noexcept
    -> comp::Tile::entity;

}  // namespace wanderer
