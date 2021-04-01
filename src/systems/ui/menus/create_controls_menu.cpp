#include "create_controls_menu.hpp"

#include "button.hpp"
#include "button_factory_system.hpp"
#include "key_bind_system.hpp"
#include "menu_factory_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);
  auto& buttons = pack.buttons;

  // clang-format off
  buttons.push_back(make_button(registry, "Return", menu_action::goto_home, 4));
  // clang-format on
}

}  // namespace

auto create_controls_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Controls", menu_id::controls);
  registry.set<comp::controls_menu>(entity);

  add_buttons(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
