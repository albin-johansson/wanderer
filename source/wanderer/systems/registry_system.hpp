#pragma once

#include <entt/entt.hpp>

namespace wanderer::sys {

/**
 * \brief Creates a main registry, used as the "top-level" registry for the game.
 *
 * \return a registry.
 */
[[nodiscard]] auto make_main_registry() -> entt::registry;

/**
 * \brief Creates a registry for use by individual levels.
 *
 * \return a registry.
 */
[[nodiscard]] auto make_level_registry() -> entt::registry;

}  // namespace wanderer::sys
