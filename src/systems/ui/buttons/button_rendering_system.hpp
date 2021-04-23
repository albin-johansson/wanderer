#pragma once

#include <entt.hpp>  // registry

#include "components/ui/button.hpp"
#include "components/ui/button_group.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Buttons
/// \{

/**
 * \brief Renders a button pack.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 * \param pack the buttons that will be rendered.
 */
void render_buttons(const entt::registry& registry,
                    graphics_context& graphics,
                    const comp::button_pack& pack);

/**
 * \brief Renders a button group.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 * \param group the buttons that will be rendered.
 */
void render_button_group(const entt::registry& registry,
                         graphics_context& graphics,
                         const comp::button_group& group);

/// \} End of buttons

}  // namespace wanderer::sys
