#pragma once

#include <entt.hpp>  // registry

#include "components/ui/checkbox.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Checkboxes
/// \{

/**
 * \brief Renders all checkboxes in the currently selected menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_checkboxes(const entt::registry& registry, graphics_context& graphics);

/// \} End of checkboxes

}  // namespace wanderer::sys