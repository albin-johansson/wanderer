#pragma once

#include <entt.hpp>  // registry

#include "components/map/level.hpp"

namespace wanderer::sys {

/// \name Levels
/// \{

/**
 * \brief Returns the currently active level.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return the currently active level.
 */
[[nodiscard]] auto current_level(entt::registry& shared) -> comp::level&;

/// \copydoc current_level()
[[nodiscard]] auto current_level(const entt::registry& shared) -> const comp::level&;

/// \} End of levels

}  // namespace wanderer::sys
