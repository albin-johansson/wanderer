#include "saves_menu_system.hpp"

#include <centurion.hpp>
#include <filesystem>

#include "button_factory_system.hpp"
#include "button_system.hpp"
#include "files_directory.hpp"
#include "grid_system.hpp"
#include "key_bind_system.hpp"
#include "make_label.hpp"
#include "make_line.hpp"
#include "menu.hpp"
#include "menu_action.hpp"
#include "menu_constants.hpp"
#include "menu_factory_system.hpp"
#include "saves_menu.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline constexpr auto x0 = convert_column_to_x(3);
inline constexpr auto x1 = convert_column_to_x(glob::menu_columns - 3);

inline constexpr auto y0 = convert_row_to_y(5);
inline constexpr auto y1 = convert_row_to_y(glob::menu_rows - 2);

[[nodiscard]] auto make_binds(entt::registry& registry)
    -> std::vector<comp::key_bind::entity>
{
  std::vector<comp::key_bind::entity> binds;

  binds.push_back(
      make_bind(registry, cen::scancodes::escape, menu_action::goto_home));

  return binds;
}

[[nodiscard]] auto make_buttons(entt::registry& registry)
    -> std::vector<comp::button::entity>
{
  std::vector<comp::button::entity> buttons;

  // clang-format off
  buttons.push_back(make_button(registry, "Return", "saves/return"_hs, menu_action::goto_home, 4));
  // clang-format on

  return buttons;
}

[[nodiscard]] auto make_lines(entt::registry& registry)
    -> std::vector<comp::line::entity>
{
  std::vector<comp::line::entity> lines;

  lines.push_back(make_line(registry, {x0, y0}, {x0, y1}));
  lines.push_back(make_line(registry, {x1, y0}, {x1, y1}));
  lines.push_back(make_line(registry, {x0, y0}, {x1, y0}));
  lines.push_back(make_line(registry, {x0, y1}, {x1, y1}));
  lines.push_back(make_line(registry,
                            {convert_column_to_x(8), y0 + 10},
                            {convert_column_to_x(8), y1 - 10}));

  return lines;
}

[[nodiscard]] auto make_labels(entt::registry& registry)
    -> std::vector<comp::label::entity>
{
  std::vector<comp::label::entity> labels;

  labels.push_back(make_label(registry, x0, y1 + 5));

  return labels;
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

void refresh_saves_menu(entt::registry& registry)
{
  registry.clear<comp::saves_menu_entry>();

  const auto saves = files_directory() / "saves";
  for (const auto& entry : std::filesystem::directory_iterator(saves))
  {
    if (entry.is_directory())
    {
      auto& item = registry.emplace<comp::saves_menu_entry>(registry.create());
      item.name = entry.path().filename().string();
    }
  }

  const auto view = registry.view<comp::menu, comp::saves_menu>();
  view.each([&](comp::menu& menu, comp::saves_menu& savesMenu) {
    // TODO

    //    const auto entity = comp::saves_menu_entry::entity{registry.create()};
    //
    //    auto& entry = registry.emplace<comp::saves_menu_entry>(entity);
    //    entry.name = "Foo";
    //
    //    const auto buttonEntity = comp::button::entity{registry.create()};
    //    auto& button = registry.emplace<comp::button>(buttonEntity);
    //    button.row = 5;
    //    button.col = 3;
    //    button.text = "Foo";
    //
    //    menu.buttons.push_back(buttonEntity);
    //    savesMenu.entries.push_back(entity);
  });
}

}  // namespace wanderer::sys
