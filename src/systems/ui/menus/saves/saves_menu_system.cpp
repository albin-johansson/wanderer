#include "saves_menu_system.hpp"

#include <cassert>     // assert
#include <cmath>       // round, fmod
#include <filesystem>  // directory_iterator
#include <format>      // format
#include <string>      // string, to_string
#include <utility>     // move

#include "components/ctx/active_menu.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/lazy_texture.hpp"
#include "components/ui/saves_menu.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/math/floating.hpp"
#include "core/utils/file_utils.hpp"
#include "io/directories.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/lazy-textures/lazy_texture_factory_system.hpp"
#include "systems/ui/menus/saves/saves_menu_entry_factory_system.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float save_entry_row = 6;
inline constexpr float save_entry_col = 6;
inline constexpr float page_indicator_row = 15.25f;
inline constexpr float page_indicator_col = 5.2f;
inline constexpr int buttons_per_page = 8;

/// Returns the number of pages necessary for a button group
[[nodiscard]] auto page_count(const comp::button_group& group) -> int
{
  return std::max(1,
                  round(group.buttons.size() / static_cast<float>(group.items_per_page)));
}

/// Returns the appropriate text for the page indicator label
[[nodiscard]] auto get_page_indicator_text(const comp::button_group& group) -> std::string
{
  return std::format("{} / {}", group.current_page + 1, page_count(group));
}

/// Clears and refreshes the save menu entries for a saves menu
void fetch_saves(entt::registry& registry, comp::saves_menu& savesMenu)
{
  destroy_and_clear(registry, savesMenu.entries);

  for (const auto& entry : std::filesystem::directory_iterator(saves_directory()))
  {
    if (entry.is_directory())
    {
      savesMenu.entries.push_back(make_saves_menu_entry(registry, entry.path()));
    }
  }
}

/// Updates whether or not the increment/decrement buttons are enabled
void update_page_indicators(entt::registry& registry)
{
  const auto entity = registry.ctx<ctx::active_menu>().entity;

  auto& menu = registry.get<comp::saves_menu>(entity);
  const auto& group = registry.get<comp::button_group>(entity);

  const auto currentPage = group.current_page;
  const auto nPages = page_count(group);

  registry.get<comp::button>(menu.decrement_button).enabled = currentPage != 0;
  registry.get<comp::button>(menu.increment_button).enabled = currentPage != nPages - 1;
}

void refresh_save_entry_buttons(entt::registry& registry,
                                comp::button_group& group,
                                const comp::menu::entity menuEntity)
{
  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);

  destroy_and_clear(registry, group.buttons);

  const auto maxRow = static_cast<float>(group.items_per_page);
  for (auto row = 0; const auto entryEntity : savesMenu.entries)
  {
    const auto& entry = registry.get<comp::saves_menu_entry>(entryEntity);
    const auto actualRow = save_entry_row + std::fmod(static_cast<float>(row), maxRow);

    const auto buttonEntity = make_button(registry,
                                          entry.name,
                                          menu_action::change_save_preview,
                                          grid_position{actualRow, save_entry_col});

    auto& button = registry.get<comp::button>(buttonEntity);
    button.visible = row < maxRow;

    auto& associatedMenu = registry.emplace<comp::associated_menu>(buttonEntity);
    associatedMenu.entity = menuEntity;

    auto& associatedEntry = registry.emplace<comp::associated_saves_entry>(buttonEntity);
    associatedEntry.entry = entryEntity;

    if (group.selected == entt::null)
    {
      group.selected = buttonEntity;
    }

    group.buttons.push_back(buttonEntity);
    ++row;
  }
}

void refresh_page_indicator_label(entt::registry& registry,
                                  comp::button_group& group,
                                  const comp::menu::entity menuEntity)
{
  if (group.indicator_label == entt::null)
  {
    group.indicator_label =
        sys::make_label(registry,
                        menuEntity,
                        get_page_indicator_text(group),
                        grid_position{page_indicator_row, page_indicator_col},
                        text_size::medium);
  }
  else
  {
    auto& label = registry.get<comp::label>(group.indicator_label);
    set_text(label, get_page_indicator_text(group));
  }
}

void refresh_saves_menu_contents(entt::registry& registry,
                                 const comp::menu::entity menuEntity)
{
  auto& group = registry.get_or_emplace<comp::button_group>(menuEntity);
  nullify(group.selected);
  group.current_page = 0;
  group.items_per_page = buttons_per_page;

  // This is strange, but required due to how the button group rendering works
  auto& associated = registry.get_or_emplace<comp::associated_menu>(menuEntity);
  associated.entity = menuEntity;

  refresh_save_entry_buttons(registry, group, menuEntity);
  refresh_page_indicator_label(registry, group, menuEntity);

  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);
  registry.get<comp::button>(savesMenu.load_button).enabled = !group.buttons.empty();
  registry.get<comp::button>(savesMenu.delete_button).enabled = !group.buttons.empty();

  update_page_indicators(registry);
}

/// Changes the currently selected saves button group page
void change_saves_button_group_page(entt::registry& registry, const int increment)
{
  const auto menu = registry.ctx<ctx::active_menu>().entity;
  if (auto* group = registry.try_get<comp::button_group>(menu))
  {
    const auto nPages = page_count(*group);
    const auto nextPage = group->current_page + increment;
    if (nextPage >= 0 && nextPage < nPages)
    {
      nullify(group->selected);
      group->current_page += increment;

      const auto firstRow = group->current_page * group->items_per_page;
      for (int row = 0; const auto buttonEntity : group->buttons)
      {
        auto& button = registry.get<comp::button>(buttonEntity);
        button.visible = row >= firstRow && row <= firstRow + (group->items_per_page - 1);

        if (button.visible && group->selected == entt::null)
        {
          group->selected = buttonEntity;
        }

        ++row;
      }

      auto& label = registry.get<comp::label>(group->indicator_label);
      set_text(label, get_page_indicator_text(*group));

      update_page_indicators(registry);
    }
  }
}

}  // namespace

void refresh_saves_menu(entt::registry& registry)
{
  registry.clear<comp::saves_menu_entry>();

  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;

  fetch_saves(registry, registry.get<comp::saves_menu>(menuEntity));
  refresh_saves_menu_contents(registry, menuEntity);
  change_save_preview(registry);
}

void change_save_preview(entt::registry& registry)
{
  const auto activeMenu = registry.ctx<ctx::active_menu>().entity;
  assert(registry.get<comp::menu>(activeMenu).id == menu_id::saves);

  auto& savesMenu = registry.get<comp::saves_menu>(activeMenu);

  destroy_if_exists(registry, savesMenu.title_label);
  destroy_if_exists(registry, savesMenu.time_label);
  destroy_if_exists(registry, savesMenu.data_version_label);
  destroy_if_exists(registry, savesMenu.preview_texture);

  auto& group = registry.get<comp::button_group>(activeMenu);
  if (group.selected != entt::null)
  {
    const auto associatedEntry =
        registry.get<comp::associated_saves_entry>(group.selected).entry;

    const auto& entry = registry.get<comp::saves_menu_entry>(associatedEntry);

    const auto label = [&](std::string text,
                           const float row,
                           const float col,
                           const text_size size = text_size::small) {
      return make_label(registry,
                        activeMenu,
                        std::move(text),
                        grid_position{row, col},
                        size);
    };

    savesMenu.title_label = label(entry.name, 6, 11, text_size::large);
    savesMenu.time_label =
        label("Last played:  " +
                  last_modified(saves_directory() / entry.name / (entry.name + ".json")),
              7.4f,
              11.0f);
    savesMenu.data_version_label =
        label(std::format("Data version: {}", entry.data_version), 8.4f, 11.0f);

    const auto width = glob::menu_col_size * 9.0f;
    const auto height = (width / 16.0f) * 9.0f;  // Assume 16:9 aspect ratio
    savesMenu.preview_texture = make_lazy_texture(registry,
                                                  activeMenu,
                                                  entry.preview,
                                                  grid_position{7.0f, 20.0f},
                                                  cen::area(width, height));
  }
}

void increment_saves_button_group_page(entt::registry& registry)
{
  change_saves_button_group_page(registry, 1);
}

void decrement_saves_button_group_page(entt::registry& registry)
{
  change_saves_button_group_page(registry, -1);
}

auto get_selected_save_name(entt::registry& shared) -> std::string
{
  const auto activeMenu = shared.ctx<ctx::active_menu>().entity;
  assert(shared.get<comp::menu>(activeMenu).id == menu_id::saves);

  auto& group = shared.get<comp::button_group>(activeMenu);
  assert(group.selected != entt::null);

  const auto associatedEntry =
      shared.get<comp::associated_saves_entry>(group.selected).entry;

  return shared.get<comp::saves_menu_entry>(associatedEntry).name;
}

}  // namespace wanderer::sys
