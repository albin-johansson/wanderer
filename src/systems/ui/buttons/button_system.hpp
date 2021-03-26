#pragma once

#include <centurion.hpp>  // mouse, renderer
#include <entt.hpp>       // registry, dispatcher

#include "button.hpp"
#include "maybe.hpp"
#include "menu.hpp"

namespace wanderer::sys {

// Checks whether or not a button was pressed, triggers its action if so
void query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::button::entity buttonEntity,
                  const cen::mouse& mouse);

// Updates the hover state of all buttons, returns the currently hovered button
[[nodiscard]] auto update_button_hover(entt::registry& registry,
                                       const comp::menu::entity menuEntity,
                                       const cen::mouse& mouse)
    -> maybe<comp::button::entity>;

}  // namespace wanderer::sys
