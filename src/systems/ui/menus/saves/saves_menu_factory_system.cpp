#include "saves_menu_factory_system.hpp"

#include <centurion.hpp>  // scancodes
#include <vector>         // vector

#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "components/ui/line.hpp"
#include "components/ui/saves_menu.hpp"
#include "core/menu_constants.hpp"
#include "io/files_directory.hpp"
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

[[nodiscard]] auto make_binds(entt::registry& registry)
    -> std::vector<comp::key_bind::entity>
{
  std::vector<comp::key_bind::entity> binds;

  binds.push_back(make_bind(registry, cen::scancodes::escape, menu_action::goto_home));

  return binds;
}

[[nodiscard]] auto make_labels(entt::registry& registry, const comp::menu::entity menu)
    -> std::vector<comp::label::entity>
{
  std::vector<comp::label::entity> labels;

  const auto label = [&](std::string text,
                         const float row,
                         const float col,
                         const text_size size = text_size::small) {
    labels.push_back(
        make_label(registry, menu, std::move(text), grid_position{row, col}, size));
  };

  label("Location:   " + (files_directory() / "saves").string(),
        glob::menu_rows - 1.7f,
        2);

  return labels;
}

[[nodiscard]] auto make_buttons(entt::registry& registry,
                                const comp::menu::entity menuEntity)
    -> std::vector<comp::button::entity>
{
  std::vector<comp::button::entity> buttons;

  const auto button = [&](std::string text,
                          const menu_action action,
                          const float row,
                          const float col = -1) {
    const auto entity =
        make_button(registry, std::move(text), action, grid_position{row, col});
    buttons.push_back(entity);
    return entity;
  };

  button("Return", menu_action::goto_home, 3.5f);

  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);

  savesMenu.loadButton = button("Load", menu_action::load_game, 15, 12);
  savesMenu.deleteButton = button("Delete", menu_action::none, 15, 27.5f);

  savesMenu.decrementButton =
      button("<", menu_action::decrement_saves_button_group_page, 15, 4);
  savesMenu.incrementButton =
      button(">", menu_action::increment_saves_button_group_page, 15, 8);

  return buttons;
}

[[nodiscard]] auto make_lines(entt::registry& registry) -> std::vector<comp::line::entity>
{
  std::vector<comp::line::entity> lines;

  const auto line = [&](const grid_position start, const grid_position end) {
    lines.push_back(make_line(registry, start, end));
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
  line({15, 3}, {15, 9});

  return lines;
}

}  // namespace

auto make_saves_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto menuEntity = make_menu(registry, "Saves", menu_id::saves);
  registry.emplace<comp::saves_menu>(menuEntity);

  auto& bindsPack = registry.emplace<comp::key_bind_pack>(menuEntity);
  bindsPack.binds = make_binds(registry);

  auto& buttonPack = registry.emplace<comp::button_pack>(menuEntity);
  buttonPack.buttons = make_buttons(registry, menuEntity);

  auto& labelPack = registry.emplace<comp::label_pack>(menuEntity);
  labelPack.labels = make_labels(registry, menuEntity);

  auto& linePack = registry.emplace<comp::line_pack>(menuEntity);
  linePack.lines = make_lines(registry);

  return menuEntity;
}

}  // namespace wanderer::sys
