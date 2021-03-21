#include "home_menu_factory_system.hpp"

#include "button.hpp"
#include "button_factory_system.hpp"
#include "menu_factory_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);

  auto& b = pack.buttons;
  b.reserve(5);

  b.push_back(make_button(registry, "Play", 7, -1, "home/play"_hs));
  b.push_back(
      make_button(registry, "Settings", 8, -1, "home/goto-settings"_hs));
  b.push_back(make_button(registry, "Saves", 9, -1, "home/goto-saves"_hs));
  b.push_back(
      make_button(registry, "Controls", 10, -1, "home/goto-controls"_hs));
  b.push_back(make_button(registry, "Quit", 11, -1, "home/quit"_hs));
}

}  // namespace

auto create_home_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Wanderer", menu_id::home);

  add_buttons(registry, entity);

  return entity;
}

}  // namespace wanderer::sys
