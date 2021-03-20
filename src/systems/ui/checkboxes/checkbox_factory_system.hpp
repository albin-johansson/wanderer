#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "checkbox.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

auto add_checkbox(entt::registry& registry,
                  std::string text,
                  const int row,
                  const int col,
                  menu_action action,
                  const bool checked = false) -> comp::checkbox::entity;

}