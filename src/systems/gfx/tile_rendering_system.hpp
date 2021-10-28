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
void RenderTile(GraphicsContext& graphics,
                const comp::Tile& tile,
                GridPosition position) noexcept;

/**
 * \brief Returns the tile that corresponds to the current frame of an animated tile.
 *
 * \details This function is used to determine what tile to render in tile animations.
 *
 * \pre `tile` must feature a `tile_animation` component.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param tile the tile entity that is animated.
 * \param tileset the associated tileset.
 *
 * \return the tile that corresponds to the current frame of the animated tile.
 */
[[nodiscard]] auto GetAnimatedTile(const entt::registry& registry,
                                   entt::entity tile,
                                   const comp::Tileset& tileset) -> const comp::Tile&;

/// \} End of tiles

}  // namespace wanderer::sys
