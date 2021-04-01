#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "button.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                menu_action action,
                int row,
                int col);

auto make_button(entt::registry& registry,
                 std::string text,
                 menu_action action,
                 int row,
                 int col = -1) -> comp::button::entity;

}  // namespace wanderer::sys
