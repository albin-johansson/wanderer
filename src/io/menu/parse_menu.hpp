#pragma once

#include <filesystem>  // path

#include "menu/menu.hpp"

namespace wanderer {

/**
 * \brief Parses a menu file and attempts to create a menu from it.
 *
 * \details This function throws if the menu file has an incorrect format.
 *
 * \param path the file path of the menu file.
 *
 * \return the parsed menu.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto parse_menu(const std::filesystem::path& path) -> menu;

}  // namespace wanderer
