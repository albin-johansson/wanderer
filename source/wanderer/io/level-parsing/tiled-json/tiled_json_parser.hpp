#pragma once

#include <filesystem>  // path

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::io {

/**
 * \brief Parses a map file using the Tiled JSON format.
 *
 * \param path the file path to the source JSON file.
 * \param graphics the associated graphics context.
 * \param cfg the current game configuration.
 *
 * \return a level registry.
 */
[[nodiscard]] auto parse_tiled_json_map(const std::filesystem::path& path,
                                        Graphics& graphics,
                                        const GameConfig& cfg) -> entt::registry;

}  // namespace wanderer::io
