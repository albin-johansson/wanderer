#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry
#include <string>         // string

#include "components/ui/checkbox.hpp"
#include "core/menu_action.hpp"

namespace wanderer::sys {

/// \name Checkboxes
/// \{

auto add_checkbox(entt::registry& registry,
                  std::string text,
                  const int row,
                  const int col,
                  menu_action action,
                  const bool checked = false) -> comp::checkbox::entity;

void render_checkboxes(const entt::registry& registry,
                       cen::renderer& renderer,
                       const comp::checkbox_pack& pack);

/// \} End of checkboxes

}  // namespace wanderer::sys