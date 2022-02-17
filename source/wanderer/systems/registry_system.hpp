#pragma once

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \brief Creates a main registry, used as the "top-level" registry for the game.
 *
 * \details The main registry has the following context components:
 * - `comp::level_ctx`
 *
 * \return a registry.
 */
[[nodiscard]] auto make_main_registry() -> entt::registry;

/**
 * \brief Creates a registry for use by individual levels.
 *
 * \details A level registry has the following context components:
 * - `comp::tilemap`
 * - `comp::tilesets`
 * - `comp::render_bounds`
 * - `comp::viewport`
 *
 * \param cfg the current game configuration.
 *
 * \return a registry.
 */
[[nodiscard]] auto make_level_registry(const game_cfg& cfg) -> entt::registry;

}  // namespace wanderer::sys
