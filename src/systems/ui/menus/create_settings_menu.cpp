#include "create_settings_menu.hpp"

#include "button_factory_system.hpp"
#include "checkbox.hpp"
#include "checkbox_factory_system.hpp"
#include "create_action.hpp"
#include "key_bind_system.hpp"
#include "menu_factory_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);
  auto& vec = pack.buttons;

  vec.push_back(make_button(registry,
                            "Return",
                            "settings/return"_hs,
                            menu_action::goto_home,
                            4));
}

void add_checkboxes(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::checkbox_pack>(entity);
  auto& vec = pack.checkboxes;

  vec.push_back(add_checkbox(registry,
                             "Integer scaling",
                             6,
                             4,
                             "settings/integer-scaling"_hs,
                             menu_action::goto_home,  // FIXME
                             true));
}

}  // namespace

auto create_settings_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Settings", menu_id::settings);

  add_buttons(registry, entity);
  add_checkboxes(registry, entity);

  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
