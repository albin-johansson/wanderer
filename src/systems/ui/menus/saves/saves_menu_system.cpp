#include "saves_menu_system.hpp"

#include <cmath>       // round, fmod
#include <filesystem>  // directory_iterator
#include <string>      // to_string
#include <utility>     // move

#include "components/ui/button_group.hpp"
#include "components/ui/label.hpp"
#include "components/ui/menu.hpp"
#include "components/ui/saves_menu.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/null_entity.hpp"
#include "ctx/active_menu.hpp"
#include "io/files_directory.hpp"
#include "io/menu/menu_action.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/labels/label_system.hpp"

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
  const auto itemsPerPage = static_cast<float>(group.itemsPerPage);
  return static_cast<int>(std::round(group.buttons.size() / itemsPerPage));
}

/// Returns the appropriate text for the page indicator label
[[nodiscard]] auto get_page_indicator_text(const comp::button_group& group) -> std::string
{
  const auto nPages = page_count(group);
  return std::to_string(group.currentPage + 1) + " / " + std::to_string(nPages);
}

/// Clears and refreshes the save menu entries for a saves menu
void fetch_saves(entt::registry& registry, comp::saves_menu& savesMenu)
{
  destroy_and_clear(registry, savesMenu.entries);

  static const auto saves = files_directory() / "saves";
  for (const auto& entry : std::filesystem::directory_iterator(saves))
  {
    if (entry.is_directory())
    {
      const auto entity = comp::saves_menu_entry::entity{registry.create()};

      auto& item = registry.emplace<comp::saves_menu_entry>(entity);
      item.name = entry.path().filename().string();

      savesMenu.entries.push_back(entity);
    }
  }
}

/// Updates whether or not the increment/decrement buttons are enabled
void update_page_indicators(entt::registry& registry)
{
  const auto entity = registry.ctx<ctx::active_menu>().entity;

  auto& menu = registry.get<comp::saves_menu>(entity);
  const auto& group = registry.get<comp::button_group>(entity);

  const auto currentPage = group.currentPage;
  const auto nPages = page_count(group);

  registry.get<comp::button>(menu.decrementButton).enabled = currentPage != 0;
  registry.get<comp::button>(menu.incrementButton).enabled = currentPage != nPages - 1;
}

void refresh_save_entry_buttons(entt::registry& registry,
                                comp::button_group& group,
                                const comp::menu::entity menuEntity)
{
  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);

  destroy_and_clear(registry, group.buttons);

  const auto maxRow = group.itemsPerPage;
  for (int row = 0; const auto entryEntity : savesMenu.entries)
  {
    const auto& entry = registry.get<comp::saves_menu_entry>(entryEntity);
    const auto actualRow = save_entry_row + std::fmod(row, maxRow);

    // TODO action
    const auto buttonEntity =
        make_button(registry, entry.name, menu_action::none, actualRow, save_entry_col);

    auto& button = registry.get<comp::button>(buttonEntity);
    button.visible = row < maxRow;

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
  if (group.indicatorLabel == entt::null)
  {
    group.indicatorLabel = sys::make_label(registry,
                                           menuEntity,
                                           get_page_indicator_text(group),
                                           page_indicator_row,
                                           page_indicator_col,
                                           text_size::medium);
  }
  else
  {
    auto& label = registry.get<comp::label>(group.indicatorLabel);
    set_text(label, get_page_indicator_text(group));
  }
}

void refresh_saves_menu_contents(entt::registry& registry,
                                 const comp::menu::entity menuEntity)
{
  auto& group = registry.get_or_emplace<comp::button_group>(menuEntity);
  nullify(group.selected);
  group.currentPage = 0;
  group.itemsPerPage = buttons_per_page;

  refresh_save_entry_buttons(registry, group, menuEntity);
  refresh_page_indicator_label(registry, group, menuEntity);

  auto& savesMenu = registry.get<comp::saves_menu>(menuEntity);
  registry.get<comp::button>(savesMenu.loadButton).enabled = !group.buttons.empty();
  registry.get<comp::button>(savesMenu.deleteButton).enabled = !group.buttons.empty();

  update_page_indicators(registry);
}

/// Changes the currently selected saves button group page
void change_saves_button_group_page(entt::registry& registry, const int increment)
{
  const auto menu = registry.ctx<ctx::active_menu>().entity;
  if (auto* group = registry.try_get<comp::button_group>(menu))
  {
    const auto nPages = page_count(*group);
    const auto nextPage = group->currentPage + increment;
    if (nextPage >= 0 && nextPage < nPages)
    {
      nullify(group->selected);
      group->currentPage += increment;

      const auto firstRow = group->currentPage * group->itemsPerPage;
      for (int row = 0; const auto buttonEntity : group->buttons)
      {
        auto& button = registry.get<comp::button>(buttonEntity);
        button.visible = row >= firstRow && row <= firstRow + (group->itemsPerPage - 1);

        if (button.visible && group->selected == entt::null)
        {
          group->selected = buttonEntity;
        }

        ++row;
      }

      auto& label = registry.get<comp::label>(group->indicatorLabel);
      set_text(label, get_page_indicator_text(*group));

      update_page_indicators(registry);
    }
  }
}

}  // namespace

void update_saves_menu(entt::registry& registry)
{
  registry.clear<comp::saves_menu_entry>();

  const auto menuEntity = registry.ctx<ctx::active_menu>().entity;

  fetch_saves(registry, registry.get<comp::saves_menu>(menuEntity));
  refresh_saves_menu_contents(registry, menuEntity);
}

void increment_saves_button_group_page(entt::registry& registry)
{
  change_saves_button_group_page(registry, 1);
}

void decrement_saves_button_group_page(entt::registry& registry)
{
  change_saves_button_group_page(registry, -1);
}

}  // namespace wanderer::sys
