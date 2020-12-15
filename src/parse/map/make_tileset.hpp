#pragma once

#include <entt.hpp>          // registry
#include <memory>            // unique_ptr
#include <step_tileset.hpp>  // tileset
#include <vector>            // vector

#include "graphics_context.hpp"
#include "tileset.hpp"

namespace wanderer {

using tileset_collection = std::vector<std::unique_ptr<step::tileset>>;

/**
 * \brief Creates a tileset based on a collection of raw tileset
 * representations.
 *
 * \param registry the registry that will be associated with the tilesets.
 * \param tilesets the collection of raw tileset representations.
 * \param graphics the graphics context that will be used.
 *
 * \return the created tileset entity.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto make_tileset(entt::registry& registry,
                                const tileset_collection& tilesets,
                                graphics_context& graphics)
    -> comp::tileset::entity;

}  // namespace wanderer
