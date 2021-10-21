#include "menu_factory_system.hpp"

#include <utility>  // move

#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"

namespace wanderer::sys {

auto MakeMenu(entt::registry& registry,
              std::string title,
              const MenuId id,
              const bool blocking) -> entt::entity
{
  const auto entity = registry.create();

  auto& menu = registry.emplace<comp::Menu>(entity);
  menu.title = std::move(title);
  menu.id = id;
  menu.blocking = blocking;

  registry.emplace<comp::MenuDrawable>(entity);

  return entity;
}

auto MakeHomeMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Wanderer", MenuId::Home);
  registry.set<comp::HomeMenu>(entity);

  MakeButton(registry, entity, "Play", MenuAction::GotoInGame, {5, -1});
  MakeButton(registry, entity, "Quick Save", MenuAction::QuickSave, {7, -1});
  MakeButton(registry, entity, "Saves", MenuAction::GotoSaves, {8, -1});
  MakeButton(registry, entity, "Settings", MenuAction::GotoSettings, {9, -1});
  MakeButton(registry, entity, "Controls", MenuAction::GotoControls, {10, -1});
  MakeButton(registry, entity, "Quit", MenuAction::Quit, {12, -1});

  AddBinds(registry,
           entity,
           comp::KeyBind{cen::scancodes::escape, MenuAction::GotoInGame});

  return entity;
}

auto MakeControlsMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Controls", MenuId::Controls);
  registry.set<comp::ControlsMenu>(entity);

  MakeButton(registry, entity, "Return", MenuAction::GotoHome, {4, -1});

  MakeLabel(registry, entity, "Move Up", {6, 13});
  MakeLabel(registry, entity, "Move Down", {7, 13});
  MakeLabel(registry, entity, "Move Left", {8, 13});
  MakeLabel(registry, entity, "Move Right", {9, 13});
  MakeLabel(registry, entity, "Attack", {10, 13});
  MakeLabel(registry, entity, "Interact", {11, 13});

  AddBinds(registry, entity, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

auto MakeInGameMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, std::string{}, MenuId::InGame, false);
  registry.set<comp::InGameMenu>(entity);

  AddBinds(registry, entity, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

}  // namespace wanderer::sys
