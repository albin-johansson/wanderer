#pragma once

#include <string>  // string

#include <entt.hpp>  // registry, entity

#include "components/ui/checkbox.hpp"
#include "core/action.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name Checkboxes
/// \{

/**
 * \brief Creates a checkbox.
 *
 * \details The created entity will feature `Button`, `ButtonDrawable` and
 * `Checkbox` components.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param text the text associated with the checkbox.
 * \param position the position of the checkbox.
 * \param action the action that will be associated with the checkbox.
 * \param checked `true` if the checkbox should be checked; `false` otherwise.
 *
 * \return the created entity.
 */
auto MakeCheckbox(entt::registry& registry,
                  std::string text,
                  GridPosition position,
                  Action action,
                  const bool checked = false) -> entt::entity;

auto MakeCheckbox(entt::registry& registry,
                  entt::entity menuEntity,
                  std::string text,
                  Action action,
                  GridPosition position,
                  const bool checked = false) -> entt::entity;

/// \} End of checkboxes

}  // namespace wanderer::sys
