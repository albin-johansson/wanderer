#pragma once

#include <centurion.hpp>  // system_cursor
#include <entt.hpp>       // registry

namespace wanderer::sys {

/// \name UI
/// \{

/**
 * \brief Enables the specified cursor.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param cursor the cursor that will be enabled.
 */
void EnableCursor(entt::registry& registry, cen::system_cursor cursor);

/// \} End of UI

}  // namespace wanderer::sys
