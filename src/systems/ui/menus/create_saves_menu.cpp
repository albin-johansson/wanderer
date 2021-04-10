#include "button.hpp"
#include "button_system.hpp"
#include "files_directory.hpp"
#include "grid_system.hpp"
#include "key_bind_system.hpp"
#include "label.hpp"
#include "label_system.hpp"
#include "line.hpp"
#include "line_system.hpp"
#include "menu_system.hpp"
#include "saves_menu.hpp"
#include "saves_menu_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto x_0 = column_to_x(2);
inline constexpr auto x_1 = column_to_x(glob::menu_columns - 2);

inline constexpr auto y_0 = row_to_y(5);
inline constexpr auto y_1 = row_to_y(glob::menu_rows - 2);

[[nodiscard]] auto make_binds(entt::registry& registry)
    -> std::vector<comp::key_bind::entity>
{
  std::vector<comp::key_bind::entity> binds;

  binds.push_back(make_bind(registry, cen::scancodes::escape, menu_action::goto_home));

  return binds;
}

[[nodiscard]] auto make_labels(entt::registry& registry)
    -> std::vector<comp::label::entity>
{
  std::vector<comp::label::entity> labels;

  labels.push_back(make_label(registry,
                              "Location: " + (files_directory() / "saves").string(),
                              x_0,
                              y_1 + 5));

  return labels;
}

[[nodiscard]] auto make_buttons(entt::registry& registry)
    -> std::vector<comp::button::entity>
{
  std::vector<comp::button::entity> buttons;

  const auto addButton = [&](std::string text,
                             const menu_action action,
                             const float row,
                             const float col = -1) {
    buttons.push_back(make_button(registry, std::move(text), action, row, col));
  };

  addButton("Return", menu_action::goto_home, 3.5f);
  addButton("Load", menu_action::load_game, 14.5f, 12);

  return buttons;
}

[[nodiscard]] auto make_lines(entt::registry& registry) -> std::vector<comp::line::entity>
{
  std::vector<comp::line::entity> lines;

  const auto addLine = [&](const cen::fpoint start, const cen::fpoint end) {
    lines.push_back(make_line(registry, start, end));
  };

  // Surrounding box
  addLine({x_0, y_0}, {x_0, y_1});
  addLine({x_1, y_0}, {x_1, y_1});
  addLine({x_0, y_0}, {x_1, y_0});
  addLine({x_0, y_1}, {x_1, y_1});

  // Vertical save entry separator
  addLine({column_to_x(10), y_0 + 10}, {column_to_x(10), y_1 - 10});

  // Horizontal bottom button separator
  addLine(from_grid(14, 11), from_grid(14, 29));

  return lines;
}

}  // namespace

auto create_saves_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto menuEntity = make_menu(registry, "Saves", menu_id::saves);
  registry.emplace<comp::saves_menu>(menuEntity);

  auto& bindsPack = registry.emplace<comp::key_bind_pack>(menuEntity);
  bindsPack.binds = make_binds(registry);

  auto& buttonPack = registry.emplace<comp::button_pack>(menuEntity);
  buttonPack.buttons = make_buttons(registry);

  auto& labelPack = registry.emplace<comp::label_pack>(menuEntity);
  labelPack.labels = make_labels(registry);

  auto& linePack = registry.emplace<comp::line_pack>(menuEntity);
  linePack.lines = make_lines(registry);

  return menuEntity;
}

}  // namespace wanderer::sys
