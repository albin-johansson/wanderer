#include "controls_menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/labels/label_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);

  const auto button = [&](std::string text,
                          const menu_action action,
                          const float row,
                          const float col = -1) {
    pack.buttons.push_back(make_button(registry, std::move(text), action, row, col));
  };

  button("Return", menu_action::goto_home, 4);
}

void add_labels(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::label_pack>(entity);

  const auto label = [&](std::string text, const float row, const float col) {
    pack.labels.push_back(sys::make_label(registry, entity, std::move(text), row, col));
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

auto make_controls_menu(entt::registry& registry) -> comp::menu::entity
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
