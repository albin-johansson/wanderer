#pragma once

#include <centurion.hpp>
#include <entt.hpp>  // registry

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
 * \param start the start point.
 * \param end the end point.
 *
 * \return the created entity.
 */
auto make_line(entt::registry& registry, cen::fpoint start, cen::fpoint end)
    -> comp::line::entity;

/// \} End of lines

}  // namespace wanderer::sys
