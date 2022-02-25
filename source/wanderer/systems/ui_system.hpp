#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/data/components/ui.hpp"
#include "wanderer/data/menu_id.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup ui-system UI System
 *
 * \brief Manages all UI related aspects, such as menus, buttons, and labels.
 */

/// \addtogroup ui-system
/// \{

/**
 * \brief Loads all game menus into a registry.
 *
 * \details The registry will have the following context components added:
 * - `comp::ui_menu_ctx`
 *
 * \param registry the registry that will host the menus.
 */
void load_menus(entt::registry& registry);

/**
 * \brief Updates the currently active menu.
 *
 * \param registry the menu registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 */
void update_menus(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input_state& input);

/**
 * \brief Changes the active menu.
 *
 * \param registry the menu registry.
 * \param menu the identifier associated with the menu to enable.
 */
void switch_menu(entt::registry& registry, menu_id menu);

/**
 * \brief Indicates whether the currently active menu is blocking.
 *
 * \param registry the menu registry.
 *
 * \return `true` if the menu is blocking; `false` otherwise.
 */
[[nodiscard]] auto is_current_menu_blocking(const entt::registry& registry) -> bool;

/// \name UI rendering
/// \{

/**
 * \brief Initializes text labels by rendering their text to textures.
 *
 * \details This function should be called very early in the render stage, since many
 * UI components feature labels that they expect to be initialized by the time they are
 * rendered.
 *
 * \param registry the registry hosting the text labels.
 * \param graphics the associated graphics context.
 *
 * \see `comp::ui_label`
 */
void init_text_labels(const entt::registry& registry, graphics_ctx& graphics);

/**
 * \brief Render the currently active menu.
 *
 * \param registry the menu registry.
 * \param graphics the associated graphics context.
 * \param settings the current settings.
 */
void render_active_menu(const entt::registry& registry,
                        graphics_ctx& graphics,
                        const settings& settings);

void render_button(const entt::registry& registry,
                   entt::entity buttonEntity,
                   graphics_ctx& graphics,
                   const settings& settings);

void render_label(const entt::registry& registry,
                  entt::entity labelEntity,
                  graphics_ctx& graphics);

void render_line(const entt::registry& registry,
                 entt::entity lineEntity,
                 graphics_ctx& graphics);

/// \} End of UI rendering

/// \} End of group ui-system

}  // namespace wanderer::sys
