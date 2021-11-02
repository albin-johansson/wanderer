#include "menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/saves_menu.hpp"
#include "core/game_constants.hpp"
#include "io/directories.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/checkboxes/checkbox_factory_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"
#include "systems/ui/lines/line_factory_system.hpp"

namespace wanderer::sys {
namespace {

auto MakeMenu(entt::registry& registry,
              std::string title,
              const MenuId id,
              const bool blocking,
              const bool renderBackground) -> entt::entity
{
  const auto entity = registry.create();

  auto& menu = registry.emplace<Menu>(entity);
  menu.title = std::move(title);
  menu.id = id;
  menu.blocking = blocking;
  menu.render_background = renderBackground;

  registry.emplace<MenuDrawable>(entity);

  return entity;
}

}  // namespace

auto MakeHomeMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Wanderer", MenuId::Home, true, true);
  registry.set<HomeMenu>(entity);

  MakeButton(registry, entity, "Play", MenuAction::GotoInGame, {5, -1});
  MakeButton(registry, entity, "Quick Save", MenuAction::QuickSave, {7, -1});
  MakeButton(registry, entity, "Saves", MenuAction::GotoSaves, {8, -1});
  MakeButton(registry, entity, "Settings", MenuAction::GotoSettings, {9, -1});
  MakeButton(registry, entity, "Controls", MenuAction::GotoControls, {10, -1});
  MakeButton(registry, entity, "Quit", MenuAction::Quit, {12, -1});

  AddBinds(registry, entity, KeyBind{cen::scancodes::escape, MenuAction::GotoInGame});

  return entity;
}

auto MakeSettingsMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Settings", MenuId::Settings, true, true);
  registry.set<SettingsMenu>(entity);

  MakeButton(registry, entity, "Return", MenuAction::GotoHome, {4, -1});

  MakeCheckbox(registry, entity, "Fullscreen", MenuAction::ToggleFullscreen, {6, 13});
  MakeCheckbox(registry,
               entity,
               "Integer scaling",
               MenuAction::ToggleIntegerScaling,
               {7, 13});

  AddBinds(registry, entity, KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

auto MakeSavesMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Saves", MenuId::Saves, true, true);
  registry.emplace<SavesMenu>(entity);

  MakeButton(registry, entity, "Return", MenuAction::GotoHome, {3.5f, -1});

  // clang-format off
  auto& menu = registry.get<SavesMenu>(entity);
  menu.load_button = MakeButton(registry, entity, "Load", MenuAction::LoadGame, {15, 12});
  menu.delete_button = MakeButton(registry, entity, "Delete", MenuAction::DeleteGame, {15.0f, 27.5f});
  menu.decrement_button = MakeButton(registry, entity, "<", MenuAction::DecrementSavesButtonGroupPage, {15, 4});
  menu.increment_button = MakeButton(registry, entity, ">", MenuAction::IncrementSavesButtonGroupPage, {15, 8});
  // clang-format on

  MakeLabel(registry,
            entity,
            "Location:   " + GetSavesDirectory().string(),
            {glob::menu_rows - 1.7f, 2});

  AddBinds(registry, entity, KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  constexpr auto col_0 = 2;
  constexpr auto col_1 = glob::menu_columns - 2;

  constexpr auto row_0 = 5;
  constexpr auto row_1 = glob::menu_rows - 2;

  // Surrounding box
  MakeLine(registry, entity, {row_0, col_0}, {row_1, col_0});
  MakeLine(registry, entity, {row_0, col_1}, {row_1, col_1});
  MakeLine(registry, entity, {row_0, col_0}, {row_0, col_1});
  MakeLine(registry, entity, {row_1, col_0}, {row_1, col_1});

  // Vertical save entry separator
  MakeLine(registry, entity, {row_0 + 0.5f, 10}, {row_1 - 0.5f, 10});

  // Horizontal bottom button separator
  MakeLine(registry, entity, {15, 11}, {15, 29});
  MakeLine(registry, entity, {15, col_0 + 1}, {15, 9});

  return entity;
}

auto MakeControlsMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Controls", MenuId::Controls, true, true);
  registry.set<ControlsMenu>(entity);

  MakeButton(registry, entity, "Return", MenuAction::GotoHome, {4, -1});

  MakeLabel(registry, entity, "Move Up", {6, 13});
  MakeLabel(registry, entity, "Move Down", {7, 13});
  MakeLabel(registry, entity, "Move Left", {8, 13});
  MakeLabel(registry, entity, "Move Right", {9, 13});
  MakeLabel(registry, entity, "Attack", {10, 13});
  MakeLabel(registry, entity, "Interact", {11, 13});

  AddBinds(registry, entity, KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

auto MakeInGameMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, std::string{}, MenuId::InGame, false, false);
  registry.set<InGameMenu>(entity);

  AddBinds(registry, entity, KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

}  // namespace wanderer::sys
