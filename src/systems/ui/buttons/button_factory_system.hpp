#pragma once

#include <entt.hpp>  // registry, id_type
#include <string>    // string

#include "button.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                entt::entity entity,
                std::string text,
                int row,
                int col,
                entt::id_type id);

[[deprecated]] auto make_button(entt::registry& registry,
                                std::string text,
                                int row,
                                int col,
                                entt::id_type id) -> comp::button::entity;

auto make_button(entt::registry& registry,
                 std::string text,
                 entt::id_type id,
                 int row,
                 int col = -1) -> comp::button::entity;

}  // namespace wanderer::sys
