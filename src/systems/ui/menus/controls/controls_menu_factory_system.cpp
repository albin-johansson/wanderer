#include "controls_menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/associated_menu.hpp"
#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_factory_system.hpp"
#include "systems/ui/labels/label_factory_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void AddButtons(entt::registry& registry, const entt::entity menuEntity)
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

void AddLabels(entt::registry& registry, const entt::entity entity)
{
  const auto label = [&](std::string text, const float row, const float col) {
    sys::MakeLabel(registry, entity, std::move(text), GridPosition{row, col});
  };

  float row = 6;
  const float col = 13;
  label("Move Up", row++, col);
  label("Move Down", row++, col);
  label("Move Left", row++, col);
  label("Move Right", row++, col);
  label("Attack", row++, col);
  label("Interact", row++, col);
}

}  // namespace

auto MakeControlsMenu(entt::registry& registry) -> entt::entity
{
  const auto entity = MakeMenu(registry, "Controls", MenuId::Controls);
  registry.set<comp::ControlsMenu>(entity);

  AddButtons(registry, entity);
  AddLabels(registry, entity);
  AddBinds(registry, entity, comp::KeyBind{cen::scancodes::escape, MenuAction::GotoHome});

  return entity;
}

}  // namespace wanderer::sys
