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
               MenuId id,
               bool blocking = true) -> entt::entity;

/// \} End of menus

}  // namespace wanderer::sys
