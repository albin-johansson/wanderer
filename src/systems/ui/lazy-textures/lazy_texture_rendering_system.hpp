#pragma once

#include <entt.hpp>  // registry

#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name UI
/// \{

/**
 * \brief Renders all lazy textures in the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_lazy_textures(const entt::registry& registry, GraphicsContext& graphics);

/// \} End of UI

}  // namespace wanderer::sys
