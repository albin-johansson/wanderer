#pragma once

#include <entt.hpp>    // registry
#include <filesystem>  // path

#include "graphics_context.hpp"
#include "tilemap.hpp"

namespace wanderer {

/**
 * \brief Parses a map file and creates a corresponding tilemap.
 *
 * \param registry the registry that will be associated with the map.
 * \param path the file path of the map file.
 * \param graphics the graphics context used.
 *
 * \return the created tilemap entity.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto parse_map(entt::registry& registry,
                             const std::filesystem::path& path,
                             graphics_context& graphics)
    -> comp::tilemap::entity;

}  // namespace wanderer
