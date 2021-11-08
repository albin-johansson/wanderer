#pragma once

#include <algorithm>  // any_of

#include <centurion.hpp>  // mouse, renderer
#include <entt.hpp>       // registry, dispatcher

#include "components/ui/button.hpp"
#include "core/common_concepts.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

/// \name Buttons
/// \{

void SetVisible(Button& button, bool visible);

void SetHovered(Button& button, bool hovered);

void SetEnabled(Button& button, bool enabled);

/**
 * \brief Checks whether or not a button was pressed, and if so, the associated action
 * will be triggered.
 *
 * \pre `buttonEntity` must feature a `button` component.
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
auto QueryButton(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 entt::entity buttonEntity,
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
[[nodiscard]] auto UpdateButtonHover(entt::registry& registry, const cen::mouse& mouse)
    -> Maybe<entt::entity>;

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
template <container_type<entt::entity> T>
[[nodiscard]] auto InButtonGroup(const T& buttons, const entt::entity button) -> bool
{
  return std::ranges::any_of(buttons, [button](const entt::entity entity) {
    return entity == button;
  });
}

/// \} End of buttons

}  // namespace wanderer::sys
