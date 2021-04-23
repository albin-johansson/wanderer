#pragma once

#include <entt.hpp>  // registry

#include "components/ui/line.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {

/// \name Lines
/// \{

/**
 * \brief Renders a group of lines.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 * \param pack the lines that will be rendered.
 */
void render_lines(const entt::registry& registry,
                  graphics_context& graphics,
                  const comp::line_pack& pack);

/// \} End of lines

}  // namespace wanderer::sys