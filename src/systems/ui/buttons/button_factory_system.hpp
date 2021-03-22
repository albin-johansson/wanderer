#pragma once

#include <entt.hpp>  // registry, id_type
#include <string>    // string

#include "button.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                entt::id_type id,
                menu_action action,
                int row,
                int col);

auto make_button(entt::registry& registry,
                 std::string text,
                 entt::id_type id,
                 menu_action action,
                 int row,
                 int col = -1) -> comp::button::entity;

}  // namespace wanderer::sys
