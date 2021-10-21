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
  AddBinds(registry, menu, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});
}

void make_labels(entt::registry& registry, const entt::entity menu)
{
  const auto label = [&](std::string text,
                         const float row,
                         const float col,
                         const text_size size = text_size::small) {
    MakeLabel(registry, menu, std::move(text), GridPosition{row, col}, size);
  };

  label("Location:   " + GetSavesDirectory().string(), glob::menu_rows - 1.7f, 2);
}

void make_buttons(entt::registry& registry, const entt::entity menuEntity)
{
  const auto button = [&](std::string text,
                          const MenuAction action,
                          const float row,
                          const float col = -1) {
    const auto entity =
        MakeButton(registry, std::move(text), action, GridPosition{row, col});

    auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
    associated.entity = menuEntity;

    return entity;
  };

  button("Return", MenuAction::GotoHome, 3.5f);

  // clang-format off
  auto& savesMenu = registry.get<comp::SavesMenu>(menuEntity);
  savesMenu.load_button = button("Load", MenuAction::LoadGame, 15, 12);
  savesMenu.delete_button = button("Delete", MenuAction::DeleteGame, 15, 27.5f);
  savesMenu.decrement_button = button("<", MenuAction::DecrementSavesButtonGroupPage, 15, 4);
  savesMenu.increment_button = button(">", MenuAction::IncrementSavesButtonGroupPage, 15, 8);
  // clang-format on
}

void make_lines(entt::registry& registry, const entt::entity menuEntity)
{
  const auto line = [&](const GridPosition start, const GridPosition end) {
    const auto entity = MakeLine(registry, start, end);

    auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
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
  const auto menuEntity = make_menu(registry, "Saves", MenuId::Saves);
  registry.emplace<comp::SavesMenu>(menuEntity);

  make_binds(registry, menuEntity);
  make_buttons(registry, menuEntity);
  make_labels(registry, menuEntity);
  make_lines(registry, menuEntity);

  return menuEntity;
}

}  // namespace wanderer::sys
