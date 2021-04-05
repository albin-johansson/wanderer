#include "saves_menu_system.hpp"

#include <filesystem>  // directory_iterator

#include "button_group.hpp"
#include "button_system.hpp"
#include "files_directory.hpp"
#include "menu.hpp"
#include "menu_action.hpp"
#include "null_entity.hpp"
#include "saves_menu.hpp"

namespace wanderer::sys {
namespace {

inline constexpr auto save_entry_row = 6;
inline constexpr auto save_entry_col = 6;

void fetch_saves(entt::registry& registry, comp::saves_menu& savesMenu)
{
  savesMenu.entries.clear();

  const auto saves = files_directory() / "saves";
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

void add_saves_button_group(entt::registry& registry,
                            const comp::menu::entity menuEntity,
                            comp::saves_menu& savesMenu)
{
  auto& group = registry.emplace_or_replace<comp::button_group>(menuEntity);
  group.selected = null<comp::button>();

  auto row = save_entry_row;
  for (const auto entryEntity : savesMenu.entries)
  {
    const auto& entry = registry.get<comp::saves_menu_entry>(entryEntity);

    const auto button =
        make_button(registry, entry.name, menu_action::none, row, save_entry_col);

    if (group.selected == entt::null)
    {
      group.selected = button;
    }

    group.buttons.push_back(button);
    ++row;
  }
}

}  // namespace

void update_saves_menu(entt::registry& registry)
{
  registry.clear<comp::saves_menu_entry>();

  const auto view = registry.view<comp::menu, comp::saves_menu>();

  const auto menuEntity = comp::menu::entity{view.front()};
  auto& savesMenu = view.get<comp::saves_menu>(menuEntity);

  fetch_saves(registry, savesMenu);
  add_saves_button_group(registry, menuEntity, savesMenu);
}

}  // namespace wanderer::sys
