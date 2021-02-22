#pragma once

#include <entt.hpp>    // registry
#include <filesystem>  // path

#include "menu.hpp"

namespace wanderer {

/**
 * \brief Parses a menu file and attempts to create a menu from it.
 *
 * \details This function throws if the menu file has an incorrect format.
 *
 * \param registry the menu registry.
 * \param path the file path of the menu file.
 *
 * \return the parsed menu entity.
 *
 * \since 0.1.0
 */
auto parse_menu(entt::registry& registry, const std::filesystem::path& path)
    -> comp::menu::entity;

}  // namespace wanderer
