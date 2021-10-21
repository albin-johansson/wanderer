#include "settings_menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/associated_menu.hpp"
#include "components/ui/checkbox.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/checkboxes/checkbox_factory_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const entt::entity menuEntity)
{
  const auto button = [&](std::string text,
                          const MenuAction action,
                          const float row,
                          const float col = -1) {
    const auto entity =
        MakeButton(registry, std::move(text), action, GridPosition{row, col});

    auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
    associated.entity = menuEntity;
  };

  button("Return", MenuAction::GotoHome, 4);
}

void add_checkboxes(entt::registry& registry, const entt::entity menuEntity)
{
  const auto checkbox =
      [&](std::string text, const float row, const float col, const MenuAction action) {
        const auto entity =
            MakeCheckbox(registry, std::move(text), GridPosition{row, col}, action);

        auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
        associated.entity = menuEntity;
      };

  checkbox("Fullscreen", 6, 13, MenuAction::ToggleFullscreen);
  checkbox("Integer scaling", 7, 13, MenuAction::ToggleIntegerScaling);
}

}  // namespace

auto make_settings_menu(entt::registry& registry) -> entt::entity
{
  const auto entity = make_menu(registry, "Settings", MenuId::Settings);
  registry.set<comp::SettingsMenu>(entity);

  add_buttons(registry, entity);
  add_checkboxes(registry, entity);

  AddBinds(registry, entity, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

}  // namespace wanderer::sys
