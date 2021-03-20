#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "button.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                const int row,
                const int col,
                const menu_action action);

auto make_button(entt::registry& registry,
                 std::string text,
                 const int row,
                 const int col,
                 const menu_action action) -> comp::button::entity;

}  // namespace wanderer::sys
