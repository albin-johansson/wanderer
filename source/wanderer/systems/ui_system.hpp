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
                  const InputState& input);

/**
 * \brief Changes the active menu.
 *
 * \param registry the menu registry.
 * \param menu the identifier associated with the menu to enable.
 */
void switch_menu(entt::registry& registry, MenuId menu);

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
void init_text_labels(const entt::registry& registry, Graphics& graphics);

/**
 * \brief Render the currently active menu.
 *
 * \param registry the menu registry.
 * \param graphics the associated graphics context.
 * \param settings the current settings.
 */
void render_active_menu(const entt::registry& registry,
                        Graphics& graphics,
                        const Settings& settings);

void render_button(const entt::registry& registry,
                   entt::entity buttonEntity,
                   Graphics& graphics,
                   const Settings& settings);

void render_label(const entt::registry& registry,
                  entt::entity labelEntity,
                  Graphics& graphics);

void render_line(const entt::registry& registry,
                 entt::entity lineEntity,
                 Graphics& graphics);

/// \} End of UI rendering

/// \} End of group ui-system

}  // namespace wanderer::sys
