#include "settings_menu_factory_system.hpp"

#include <string>   // string
#include <utility>  // move

#include "components/ui/checkbox.hpp"
#include "systems/input/key_bind_system.hpp"
#include "systems/ui/buttons/button_system.hpp"
#include "systems/ui/checkboxes/checkbox_system.hpp"
#include "systems/ui/menus/menu_system.hpp"

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

void add_checkboxes(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::checkbox_pack>(entity);

  const auto checkbox = [&](std::string text,
                            const float row,
                            const float col,
                            const menu_action action) {
    pack.checkboxes.push_back(add_checkbox(registry, std::move(text), row, col, action));
  };

  checkbox("Fullscreen", 6, 13, menu_action::toggle_fullscreen);
  checkbox("Integer scaling", 7, 13, menu_action::toggle_integer_scaling);
  checkbox("Simulate lights", 8, 13, menu_action::toggle_lights);
}

}  // namespace

auto make_settings_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Settings", menu_id::settings);
  registry.set<comp::settings_menu>(entity);

  add_buttons(registry, entity);
  add_checkboxes(registry, entity);

  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
