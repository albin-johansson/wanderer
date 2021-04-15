#include "create_home_menu.hpp"

#include "button.hpp"
#include "button_system.hpp"
#include "key_bind_system.hpp"
#include "menu_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);

  auto& b = pack.buttons;
  b.reserve(5);

  // clang-format off
  float row = 5;
  b.push_back(make_button(registry, "Play", menu_action::goto_in_game, row++));

  ++row;
  b.push_back(make_button(registry, "Quick Save", menu_action::quick_save, row++));
  b.push_back(make_button(registry, "Saves", menu_action::goto_saves, row++));
  b.push_back(make_button(registry, "Settings", menu_action::goto_settings, row++));
  b.push_back(make_button(registry, "Controls", menu_action::goto_controls, row++));

  b.push_back(make_button(registry, "Quit", menu_action::quit, 13));
  // clang-format on
}

}  // namespace

auto create_home_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Wanderer", menu_id::home);
  registry.set<comp::home_menu>(entity);

  add_buttons(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_in_game});

  return entity;
}

}  // namespace wanderer::sys
