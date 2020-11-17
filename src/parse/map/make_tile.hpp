#pragma once

#include <cen/rect.hpp>
#include <cen/texture.hpp>
#include <entt.hpp>
#include <step_tile.hpp>

#include "component/tile.hpp"
#include "texture_handle.hpp"
#include "tile_id.hpp"

namespace wanderer {

void parse_fancy_tile(entt::registry& registry,
                      comp::tile::entity tileEntity,
                      const step::tile& stepTile,
                      tile_id firstGid);

[[nodiscard]] auto make_basic_tile(entt::registry& registry,
                                   tile_id id,
                                   const texture_handle& sheet,
                                   const cen::irect& src) noexcept
    -> comp::tile::entity;

}  // namespace wanderer
