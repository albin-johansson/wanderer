#pragma once

#include <entt.hpp>  // registry

#include "components/ui/checkbox.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Checkboxes
/// \{

/**
 * \brief Renders a group of checkboxes.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 * \param pack the checkboxes that will be rendered.
 */
void render_checkboxes(const entt::registry& registry,
                       graphics_context& graphics,
                       const comp::checkbox_pack& pack);

/// \} End of checkboxes

}  // namespace wanderer::sys