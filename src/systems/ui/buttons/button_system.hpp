#pragma once

#include <centurion.hpp>  // mouse, renderer
#include <entt.hpp>       // registry, dispatcher
#include <ranges>         // any_of

#include "components/ui/button.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/menu.hpp"
#include "core/aliases/maybe.hpp"
#include "core/common_concepts.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name Buttons
/// \{

void set_visible(comp::button& button, bool visible);

void set_hovered(comp::button& button, bool hovered);

void set_enabled(comp::button& button, bool enabled);

/**
 * \brief Checks whether or not a button was pressed, and if so, the associated action
 * will be triggered.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param buttonEntity the button entity that will be checked.
 * \param mouse the mouse state.
 *
 * \return `true` if the button was pressed; `false` otherwise.
 */
auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::button::entity buttonEntity,
                  const cen::mouse& mouse) -> bool;

// Updates the hover state of all buttons, returns the currently hovered button

/**
 * \brief Updates the button hovering in the currently active menu.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param mouse the mouse state.
 *
 * \return the currently hovered button entity; `std::nullopt` if there is none.
 */
[[nodiscard]] auto update_button_hover(entt::registry& registry, const cen::mouse& mouse)
    -> maybe<comp::button::entity>;

/**
 * \brief Indicates whether or not a button entity is in a button entity collection.
 *
 * \tparam T the container type, that contains button entities.
 *
 * \ingroup systems
 *
 * \param buttons the button entity container that will be searched.
 * \param button the button entity to look for.
 *
 * \return `true` if the container contains the specified entity; `false` otherwise.
 */
template <container_type<comp::button::entity> T>
[[nodiscard]] auto in_button_group(const T& buttons, const comp::button::entity button)
    -> bool
{
  return std::ranges::any_of(buttons, [button](const comp::button::entity entity) {
    return entity.get() == button;
  });
}

/// \} End of buttons

}  // namespace wanderer::sys
