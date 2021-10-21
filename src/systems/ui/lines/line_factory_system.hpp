#pragma once

#include <entt.hpp>  // registry, entity

#include "components/ui/line.hpp"

namespace wanderer::sys {

/// \name Lines
/// \{

/**
 * \brief Creates a line entity.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param start the start position.
 * \param end the end position.
 *
 * \return the created entity.
 */
auto MakeLine(entt::registry& registry, GridPosition start, GridPosition end)
    -> entt::entity;

auto MakeLine(entt::registry& registry,
              entt::entity menuEntity,
              GridPosition start,
              GridPosition end) -> entt::entity;

/// \} End of lines

}  // namespace wanderer::sys
