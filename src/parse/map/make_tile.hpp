#pragma once

#include <cen/rect.hpp>
#include <cen/texture.hpp>
#include <entt.hpp>
#include <step_tile.hpp>

#include "texture_handle.hpp"
#include "tile.hpp"
#include "tile_id.hpp"

namespace wanderer {

/**
 * \brief Parses a "fancy" tile, that is a tile with extra features such as
 * animations, etc.
 *
 * \details This function can add additional components to tiles such as
 * hitboxes, animations and depth heuristics.
 *
 * \note All fancy tiles are initially "basic" tiles.
 *
 * \param registry the registry associated with the tile.
 * \param tileEntity the basic tile entity.
 * \param stepTile the tile representation.
 * \param firstGid the first global ID of the tileset that the tile resides in.
 *
 * \since 0.1.0
 */
void parse_fancy_tile(entt::registry& registry,
                      comp::tile::entity tileEntity,
                      const step::tile& stepTile,
                      tile_id firstGid);

/**
 * \brief Creates a basic tile.
 *
 * \details This function creates an entity with a `comp::tile` component.
 *
 * \param registry the registry that will be associated with the tile.
 * \param id the ID of the tile.
 * \param sheet the tileset image associated with the tile.
 * \param src the source rectangle of the tile.
 *
 * \return the created tile entity.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto make_basic_tile(entt::registry& registry,
                                   tile_id id,
                                   const texture_handle& sheet,
                                   const cen::irect& src) noexcept
    -> comp::tile::entity;

}  // namespace wanderer
