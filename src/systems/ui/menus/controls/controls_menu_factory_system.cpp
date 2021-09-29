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

void add_buttons(entt::registry& registry, const entt::entity menuEntity)
{
  const auto button = [&](std::string text,
                          const menu_action action,
                          const float row,
                          const float col = -1) {
    const auto entity =
        make_button(registry, std::move(text), action, grid_position{row, col});

    auto& associated = registry.emplace<comp::associated_menu>(entity);
    associated.entity = menuEntity;
  };

  button("Return", menu_action::goto_home, 4);
}

void add_labels(entt::registry& registry, const entt::entity entity)
{
  const auto label = [&](std::string text, const float row, const float col) {
    sys::make_label(registry, entity, std::move(text), grid_position{row, col});
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

auto make_controls_menu(entt::registry& registry) -> entt::entity
{
  const auto entity = make_menu(registry, "Controls", menu_id::controls);
  registry.set<comp::controls_menu>(entity);

  add_buttons(registry, entity);
  add_labels(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
