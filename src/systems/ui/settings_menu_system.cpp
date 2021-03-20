#include "settings_menu_system.hpp"

#include "button_factory_system.hpp"
#include "checkbox.hpp"
#include "checkbox_factory_system.hpp"
#include "create_action.hpp"
#include "menu_factory_system.hpp"

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);

  auto& vec = pack.buttons;
  vec.reserve(1);

  vec.push_back(make_button(registry, "Return", 4, -1, menu_action::goto_home));
}

void add_checkboxes(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::checkbox_pack>(entity);

  auto& vec = pack.checkboxes;
  vec.reserve(1);

  vec.push_back(add_checkbox(registry,
                             "Integer scaling",
                             6,
                             4,
                             menu_action::goto_home,
                             true));
}

}  // namespace

auto create_settings_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Settings", menu_id::settings);

  add_buttons(registry, entity);
  add_checkboxes(registry, entity);

  return entity;
}

}  // namespace wanderer::sys
