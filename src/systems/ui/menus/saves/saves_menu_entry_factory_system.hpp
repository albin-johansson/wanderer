#pragma once

#include <filesystem>  // path

#include <entt/entt.hpp>  // registry

#include "components/ui/saves_menu.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/**
 * \brief Creates a saves menu entry entity.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param dir the path of the save file directory.
 *
 * \return
 */
auto MakeSavesMenuEntry(entt::registry& registry, const std::filesystem::path& dir)
    -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
