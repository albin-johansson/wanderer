#pragma once

#include <centurion.hpp>  // mouse, renderer
#include <entt.hpp>       // registry, dispatcher

#include "button.hpp"
#include "button_group.hpp"
#include "maybe.hpp"
#include "menu.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                menu_action action,
                float row,
                float col);

auto make_button(entt::registry& registry,
                 std::string text,
                 menu_action action,
                 float row,
                 float col = -1) -> comp::button::entity;

// Checks whether or not a button was pressed, triggers its action if so
auto query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::button::entity buttonEntity,
                  const cen::mouse& mouse) -> bool;

// Updates the hover state of all buttons, returns the currently hovered button
[[nodiscard]] auto update_button_hover(entt::registry& registry,
                                       const comp::menu::entity menuEntity,
                                       const cen::mouse& mouse)
    -> maybe<comp::button::entity>;

void render_button(const entt::registry& registry,
                   cen::renderer& renderer,
                   comp::button::entity button);

void render_buttons(const entt::registry& registry,
                    cen::renderer& renderer,
                    const comp::button_pack& pack);

void render_button_group(const entt::registry& registry,
                         cen::renderer& renderer,
                         const comp::button_group& group);

}  // namespace wanderer::sys
