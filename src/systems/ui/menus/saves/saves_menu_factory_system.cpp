#include "saves_menu_factory_system.hpp"

#include <centurion.hpp>  // scancodes
#include <vector>         // vector

#include "components/ui/associated_menu.hpp"
#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "components/ui/line.hpp"
#include "components/ui/saves_menu.hpp"
#include "core/game_constants.hpp"
#include "io/directories.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"
#include "systems/ui/lines/line_factory_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto col_0 = 2;
inline constexpr auto col_1 = glob::menu_columns - 2;

inline constexpr auto row_0 = 5;
inline constexpr auto row_1 = glob::menu_rows - 2;

void make_binds(entt::registry& registry, const entt::entity menu)
{
  add_binds(registry,
            menu,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});
}

void make_labels(entt::registry& registry, const entt::entity menu)
{
  const auto label = [&](std::string text,
                         const float row,
                         const float col,
                         const text_size size = text_size::small) {
    make_label(registry, menu, std::move(text), grid_position{row, col}, size);
  };

  label("Location:   " + saves_directory().string(), glob::menu_rows - 1.7f, 2);
}

void make_buttons(entt::registry& registry, const entt::entity menuEntity)
{
  const auto button = [&](std::string text,
                          const menu_action action,
                          const float row,
                          const float col = -1) {
    const auto entity =
        make_button(registry, std::move(text), action, grid_position{row, col});

    auto& associated = registry.emplace<comp::associated_menu>(entity);
    associated.entity = menuEntity;

    return entity;
  };

  button("Return", menu_action::goto_home, 3.5f);

  // clang-format off
  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);
  savesMenu.load_button = button("Load", menu_action::load_game, 15, 12);
  savesMenu.delete_button = button("Delete", menu_action::delete_game, 15, 27.5f);
  savesMenu.decrement_button = button("<", menu_action::decrement_saves_button_group_page, 15, 4);
  savesMenu.increment_button = button(">", menu_action::increment_saves_button_group_page, 15, 8);
  // clang-format on
}

void make_lines(entt::registry& registry, const entt::entity menuEntity)
{
  const auto line = [&](const grid_position start, const grid_position end) {
    const auto entity = make_line(registry, start, end);

    auto& associated = registry.emplace<comp::associated_menu>(entity);
    associated.entity = menuEntity;
  };

  // Surrounding box
  line({row_0, col_0}, {row_1, col_0});
  line({row_0, col_1}, {row_1, col_1});
  line({row_0, col_0}, {row_0, col_1});
  line({row_1, col_0}, {row_1, col_1});

  // Vertical save entry separator
  line({row_0 + 0.5f, 10}, {row_1 - 0.5f, 10});

  // Horizontal bottom button separator
  line({15, 11}, {15, 29});
  line({15, col_0 + 1}, {15, 9});
}

}  // namespace

auto make_saves_menu(entt::registry& registry) -> entt::entity
{
  const auto menuEntity = make_menu(registry, "Saves", menu_id::saves);
  registry.emplace<comp::saves_menu>(menuEntity);

  make_binds(registry, menuEntity);
  make_buttons(registry, menuEntity);
  make_labels(registry, menuEntity);
  make_lines(registry, menuEntity);

  return menuEntity;
}

}  // namespace wanderer::sys
