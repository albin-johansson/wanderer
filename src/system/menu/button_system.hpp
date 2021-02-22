#pragma once

#include <cen/mouse_state.hpp>  // mouse_state
#include <cen/renderer.hpp>     // renderer
#include <entt.hpp>             // registry, dispatcher

#include "button.hpp"
#include "maybe.hpp"
#include "menu.hpp"

namespace wanderer::sys {

// Checks whether or not a button was pressed, triggers its action if so
void query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::button::entity buttonEntity,
                  const cen::mouse_state& mouseState);

// Updates the hover state of all buttons, returns the currently hovered button
[[nodiscard]] auto update_button_hover(entt::registry& registry,
                                       const comp::menu::entity menuEntity,
                                       const cen::mouse_state& mouseState)
    -> maybe<comp::button::entity>;

void render_button(const entt::registry& registry,
                   comp::button::entity buttonEntity,
                   cen::renderer& renderer);

}  // namespace wanderer::sys
