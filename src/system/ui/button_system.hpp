#pragma once

#include <cen/mouse_state.hpp>  // mouse_state
#include <cen/renderer.hpp>     // renderer
#include <entt.hpp>             // registry, dispatcher
#include <string>               // string

#include "button.hpp"
#include "game_constants.hpp"
#include "maybe.hpp"
#include "menu.hpp"
#include "menu_action.hpp"
#include "menu_constants.hpp"

namespace wanderer::sys {

[[nodiscard]] constexpr auto convert_column_to_x(const int column) -> int
{
  // make centered if column index is -1
  if (column == -1) {
    return (glob::logical_width<int> / 2);
  } else {
    return (column * glob::menu_col_size);
  }
}

[[nodiscard]] constexpr auto convert_row_to_y(const int row) -> int
{
  return (row * glob::menu_col_size);
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const int row,
                 const int col,
                 const menu_action action) -> comp::button::entity;

// Checks whether or not a button was pressed, triggers its action if so
void query_button(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  comp::button::entity buttonEntity,
                  const cen::mouse_state& mouseState);

// Updates the hover state of all buttons, returns the currently hovered button
[[nodiscard]] auto update_button_hover(entt::registry& registry,
                                       const comp::menu::entity menuEntity,
                                       const cen::mouse_state& mouseState)
    -> maybe<comp::button::entity>;

void render_button(const entt::registry& registry,
                   comp::button::entity buttonEntity,
                   cen::renderer& renderer);

}  // namespace wanderer::sys
