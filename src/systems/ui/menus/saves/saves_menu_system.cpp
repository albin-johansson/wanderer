#include "saves_menu_system.hpp"

#include "systems/ui/lazy-textures/lazy_texture_factory_system.hpp"

#include <algorithm>   // remove_if, max
#include <cassert>     // assert
#include <cmath>       // round, fmod, ceil
#include <filesystem>  // directory_iterator
#include <format>      // format
#include <string>      // string, to_string
#include <utility>     // move

#include "components/ui/associated_menu.hpp"
#include "components/ui/button_group.hpp"
#include "components/ui/lazy_texture.hpp"
#include "components/ui/menu.hpp"
#include "components/ui/saves_menu.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/game_constants.hpp"
#include "core/math/floating.hpp"
#include "core/utils/file_utils.hpp"
#include "io/directories.hpp"
#include "io/saves/delete_save.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/menus/saves/saves_menu_entry_factory_system.hpp"

namespace wanderer::sys {
namespace {

constexpr float save_entry_row = 6;
constexpr float save_entry_col = 6;
constexpr float page_indicator_row = 15.25f;
constexpr float page_indicator_col = 5.2f;
constexpr int32 buttons_per_page = 8;

/// Returns the number of pages necessary for a button group
[[nodiscard]] auto GetPageCount(const ButtonGroup& group) -> int
{
  return std::max(1,
                  round(std::ceil(static_cast<float>(group.buttons.size()) /
                                  static_cast<float>(group.items_per_page))));
}

/// Returns the appropriate text for the page indicator label
[[nodiscard]] auto GetPageIndicatorText(const ButtonGroup& group) -> std::string
{
  return std::format("{} / {}", group.current_page + 1, GetPageCount(group));
}

/// Clears and refreshes the save menu entries for a saves menu
void FetchSaves(entt::registry& registry, SavesMenu& savesMenu)
{
  destroy_and_clear(registry, savesMenu.entries);
  registry.clear<SavesMenuEntry>();

  for (const auto& entry : std::filesystem::directory_iterator(GetSavesDirectory())) {
    if (entry.is_directory()) {
      savesMenu.entries.push_back(MakeSavesMenuEntry(registry, entry.path()));
    }
  }
}

/// Updates whether or not the increment/decrement buttons are enabled
void UpdatePageIndicators(entt::registry& registry)
{
  const auto entity = registry.ctx<ActiveMenu>().entity;

  auto& menu = registry.get<SavesMenu>(entity);
  const auto& group = registry.get<ButtonGroup>(entity);

  const auto currentPage = group.current_page;
  const auto nPages = GetPageCount(group);

  SetEnabled(registry.get<Button>(menu.decrement_button), currentPage != 0);
  SetEnabled(registry.get<Button>(menu.increment_button), currentPage != nPages - 1);
}

void RefreshSaveEntryButtons(entt::registry& registry,
                             ButtonGroup& group,
                             const entt::entity menuEntity)
{
  auto& savesMenu = registry.get<SavesMenu>(menuEntity);

  destroy_and_clear(registry, group.buttons);

  const auto maxRow = static_cast<float>(group.items_per_page);
  for (auto row = 0; const auto entryEntity : savesMenu.entries) {
    const auto& entry = registry.get<SavesMenuEntry>(entryEntity);
    const auto actualRow = save_entry_row + std::fmod(static_cast<float>(row), maxRow);

    const auto buttonEntity = MakeButton(registry,
                                         entry.name,
                                         Action::ChangeSavePreview,
                                         GridPosition{actualRow, save_entry_col});

    SetVisible(registry.get<Button>(buttonEntity), static_cast<float>(row) < maxRow);

    auto& associatedMenu = registry.emplace<AssociatedMenu>(buttonEntity);
    associatedMenu.entity = menuEntity;

    auto& associatedEntry = registry.emplace<AssociatedSavesEntry>(buttonEntity);
    associatedEntry.entry = entryEntity;

    if (group.selected == entt::null) {
      group.selected = buttonEntity;
    }

    group.buttons.push_back(buttonEntity);
    ++row;
  }
}

void RefreshPageIndicatorLabel(entt::registry& registry,
                               ButtonGroup& group,
                               const entt::entity menuEntity)
{
  if (group.indicator_label == entt::null) {
    group.indicator_label =
        sys::MakeLabel(registry,
                       menuEntity,
                       GetPageIndicatorText(group),
                       GridPosition{page_indicator_row, page_indicator_col},
                       TextSize::Medium);
  }
  else {
    auto& label = registry.get<Label>(group.indicator_label);
    SetText(label, GetPageIndicatorText(group));
  }
}

void UpdateDeleteButtonEnabled(entt::registry& registry,
                               ButtonGroup& group,
                               const entt::entity deleteButtonEntity)
{
  if (group.selected != entt::null) {
    const auto& button = registry.get<Button>(group.selected);
    auto& deleteButton = registry.get<Button>(deleteButtonEntity);
    SetEnabled(deleteButton, button.text != "exit_save");
  }
}

void RefreshSavesMenuContents(entt::registry& registry, const entt::entity menuEntity)
{
  auto& group = registry.get_or_emplace<ButtonGroup>(menuEntity);
  group.selected = entt::null;
  group.current_page = 0;
  group.items_per_page = buttons_per_page;

  // This is strange, but required due to how the button group rendering works
  auto& associated = registry.get_or_emplace<AssociatedMenu>(menuEntity);
  associated.entity = menuEntity;

  RefreshSaveEntryButtons(registry, group, menuEntity);
  RefreshPageIndicatorLabel(registry, group, menuEntity);

  auto& savesMenu = registry.get<SavesMenu>(menuEntity);
  SetEnabled(registry.get<Button>(savesMenu.load_button), !group.buttons.empty());
  SetEnabled(registry.get<Button>(savesMenu.delete_button), !group.buttons.empty());

  UpdateDeleteButtonEnabled(registry, group, savesMenu.delete_button);
  UpdatePageIndicators(registry);
}

/// Changes the currently selected saves button group page
void ChangeSavesButtonGroupPage(entt::registry& registry, const int increment)
{
  const auto menu = registry.ctx<ActiveMenu>().entity;
  if (auto* group = registry.try_get<ButtonGroup>(menu)) {
    const auto nPages = GetPageCount(*group);
    const auto nextPage = group->current_page + increment;
    if (nextPage >= 0 && nextPage < nPages) {
      group->selected = entt::null;
      group->current_page += increment;

      const auto firstRow = group->current_page * group->items_per_page;
      for (int32 row = 0; const auto buttonEntity : group->buttons) {
        auto& button = registry.get<Button>(buttonEntity);
        SetVisible(button,
                   row >= firstRow && row <= firstRow + (group->items_per_page - 1));

        if ((button.state & Button::visible_bit) && group->selected == entt::null) {
          group->selected = buttonEntity;
        }

        ++row;
      }

      auto& label = registry.get<Label>(group->indicator_label);
      SetText(label, GetPageIndicatorText(*group));

      UpdatePageIndicators(registry);
      UpdateDeleteButtonEnabled(registry,
                                *group,
                                registry.get<SavesMenu>(menu).delete_button);
    }
  }
}

}  // namespace

void RefreshSavesMenu(entt::registry& registry)
{
  const auto menuEntity = registry.ctx<ActiveMenu>().entity;
  assert(registry.all_of<SavesMenu>(menuEntity));

  auto& savesMenu = registry.get<SavesMenu>(menuEntity);
  FetchSaves(registry, savesMenu);
  RefreshSavesMenuContents(registry, menuEntity);
  ChangeSavePreview(registry);
}

void ChangeSavePreview(entt::registry& registry)
{
  const auto activeMenu = registry.ctx<ActiveMenu>().entity;
  assert(registry.get<Menu>(activeMenu).id == MenuId::Saves);

  auto& savesMenu = registry.get<SavesMenu>(activeMenu);

  destroy_if_exists(registry, savesMenu.title_label);
  destroy_if_exists(registry, savesMenu.time_label);
  destroy_if_exists(registry, savesMenu.preview_texture);

  auto& group = registry.get<ButtonGroup>(activeMenu);
  if (group.selected != entt::null) {
    const auto associatedEntry = registry.get<AssociatedSavesEntry>(group.selected).entry;

    const auto& entry = registry.get<SavesMenuEntry>(associatedEntry);

    const auto label = [&](std::string text,
                           const float row,
                           const float col,
                           const TextSize size = TextSize::Small) {
      return MakeLabel(registry,
                       activeMenu,
                       std::move(text),
                       GridPosition{row, col},
                       size);
    };

    savesMenu.title_label = label(entry.name, 6, 11, TextSize::Large);
    savesMenu.time_label =
        label("Last played:  " +
                  GetLastModified(GetSavesDirectory() / entry.name / "data.wanderer"),
              7.4f,
              11.0f);

    const auto width = glob::menu_col_size * 9.0f;
    const auto height = (width / 16.0f) * 9.0f;  // Assume 16:9 aspect ratio
    savesMenu.preview_texture = MakeLazyTexture(registry,
                                                activeMenu,
                                                entry.preview,
                                                GridPosition{7.0f, 20.0f},
                                                cen::area(width, height));

    UpdateDeleteButtonEnabled(registry, group, savesMenu.delete_button);
  }
}

void RemoveSaveEntry(entt::registry& registry, const std::string& name)
{
  const auto activeMenu = registry.ctx<ActiveMenu>().entity;
  assert(registry.get<Menu>(activeMenu).id == MenuId::Saves);

  auto& savesMenu = registry.get<SavesMenu>(activeMenu);

  const auto range = std::ranges::remove_if(savesMenu.entries, [&](entt::entity entity) {
    const auto& entry = registry.get<SavesMenuEntry>(entity);
    return entry.name == name;
  });

  for (const auto entity : range) {
    registry.destroy(entity);
  }

  savesMenu.entries.erase(range.begin(), range.end());

  DeleteSave(name);
  RefreshSavesMenu(registry);
}

void IncrementSavesButtonGroupPage(entt::registry& registry)
{
  ChangeSavesButtonGroupPage(registry, 1);
}

void DecrementSavesButtonGroupPage(entt::registry& registry)
{
  ChangeSavesButtonGroupPage(registry, -1);
}

auto GetSelectedSaveName(entt::registry& shared) -> std::string
{
  const auto activeMenu = shared.ctx<ActiveMenu>().entity;
  assert(shared.get<Menu>(activeMenu).id == MenuId::Saves);

  auto& group = shared.get<ButtonGroup>(activeMenu);
  assert(group.selected != entt::null);

  const auto associatedEntry = shared.get<AssociatedSavesEntry>(group.selected).entry;

  return shared.get<SavesMenuEntry>(associatedEntry).name;
}

}  // namespace wanderer::sys
