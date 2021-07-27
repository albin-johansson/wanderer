#pragma once

#include "components/tile.hpp"
#include "components/tileset.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name Tiles
/// \{

/**
 * \brief Renders a single tile.
 *
 * \ingroup systems
 *
 * \param graphics the graphics context that will be used.
 * \param tile the tile that will be rendered.
 * \param position the grid position of the tile.
 */
void render_tile(graphics_context& graphics,
                 const comp::tile& tile,
                 grid_position position) noexcept;

/**
 * \brief Returns the tile that corresponds to the current frame of an animated tile.
 *
 * \details This function is used to determine what tile to render in tile animations.
 *
 * \pre `tile` must feature a `comp::tile_animation` component.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param tile the tile entity that is animated.
 * \param tileset the associated tileset.
 *
 * \return the tile that corresponds to the current frame of the animated tile.
 */
[[nodiscard]] auto get_animated_tile(const entt::registry& registry,
                                     comp::tile::entity tile,
                                     const comp::tileset& tileset) -> const comp::tile&;

/// \} End of tiles

}  // namespace wanderer::sys
