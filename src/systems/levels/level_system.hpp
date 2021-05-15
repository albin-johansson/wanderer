#pragma once

#include <entt.hpp>  // registry

#include "components/map/level.hpp"

namespace wanderer::sys {

/// \name Levels
/// \{

/**
 * \brief Returns the currently active level entity.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry that holds the levels.
 *
 * \return the currently active level entity.
 */
[[nodiscard]] auto current_level_entity(const entt::registry& shared)
    -> comp::level::entity;

/// \} End of levels

}  // namespace wanderer::sys
