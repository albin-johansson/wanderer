#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "components/ui/menu.hpp"
#include "core/menu_id.hpp"

namespace wanderer::sys {

/// \name Menus
/// \{

/// Creates a menu entity
auto make_menu(entt::registry& registry,
               std::string title,
               menu_id id,
               bool blocking = true) -> comp::menu::entity;

/// Creates and returns a menu registry
[[nodiscard]] auto make_menus() -> entt::registry;

/// \} End of menus

}  // namespace wanderer::sys
