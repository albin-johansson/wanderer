#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/**
 * \brief Creates a registry that contains data shared between various levels.
 *
 * \details The created registry will contain all menus, settings, binds, cursors, time
 * information, etc.
 *
 * \ingroup systems
 *
 * \return the created registry.
 */
[[nodiscard]] auto MakeSharedRegistry() -> entt::registry;

}  // namespace wanderer::sys
