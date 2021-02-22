#pragma once

#include <cen/mouse_state.hpp>  // mouse_state
#include <cen/renderer.hpp>     // renderer
#include <entt.hpp>             // registry, dispatcher

#include "button.hpp"
#include "maybe.hpp"
#include "menu.hpp"

namespace wanderer::sys {

auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const cen::mouse_state& mouseState,
                  comp::button::entity buttonEntity) -> bool;

[[nodiscard]] auto update_button_hover(entt::registry& registry,
                                       const comp::menu::entity menuEntity,
                                       const cen::mouse_state& mouseState)
    -> maybe<comp::button::entity>;

void render_button(const entt::registry& registry,
                   cen::renderer& renderer,
                   comp::button::entity buttonEntity);

}  // namespace wanderer::sys
