#pragma once

#include <entt/entt.hpp>

#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup registry-system Registry system
 */

/// \addtogroup registry-system
/// \{

/**
 * \brief Creates a main registry, used as the "top-level" registry for the game.
 *
 * \details The main registry has the following context components:
 * - `game_cfg`
 * - `comp::level_ctx`
 * - `comp::ui_menu_ctx`
 *
 * \param cfg the immutable game configuration added as a context component.
 *
 * \return a registry.
 */
[[nodiscard]] auto make_main_registry(const game_cfg& cfg) -> entt::registry;

/**
 * \brief Creates a registry for use by individual levels.
 *
 * \details A level registry has the following context components:
 * - `game_cfg`
 * - `comp::tilemap`
 * - `comp::tilesets`
 * - `comp::render_bounds`
 * - `comp::viewport`
 *
 * \param cfg the immutable game configuration added as a context component.
 *
 * \return a registry.
 */
[[nodiscard]] auto make_level_registry(const game_cfg& cfg) -> entt::registry;

/// \} End of group registry-system

}  // namespace wanderer::sys
