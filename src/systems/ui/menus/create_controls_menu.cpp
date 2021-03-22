#include "create_controls_menu.hpp"

#include "button.hpp"
#include "button_factory_system.hpp"
#include "menu_factory_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);
  auto& buttons = pack.buttons;

  // clang-format off
  buttons.push_back(make_button(registry, "Return", "controls/return"_hs, menu_action::goto_home, 4));
  // clang-format on
}

}  // namespace

auto create_controls_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Controls", menu_id::controls);

  add_buttons(registry, entity);

  return entity;
}

}  // namespace wanderer::sys
