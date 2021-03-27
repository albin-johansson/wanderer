#include "create_home_menu.hpp"

#include "button.hpp"
#include "button_factory_system.hpp"
#include "key_bind_system.hpp"
#include "menu_factory_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline constexpr auto play = "play"_hs;
inline constexpr auto goto_settings = "goto-settings"_hs;
inline constexpr auto goto_saves = "goto-saves"_hs;
inline constexpr auto goto_controls = "goto-controls"_hs;
inline constexpr auto quit = "quit"_hs;

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);

  auto& b = pack.buttons;
  b.reserve(5);

  // clang-format off
  b.push_back(make_button(registry, "Play", play, menu_action::goto_in_game, 6));
  b.push_back(make_button(registry, "Settings", goto_settings, menu_action::goto_settings, 7));
  b.push_back(make_button(registry, "Saves", goto_saves, menu_action::goto_saves, 8));
  b.push_back(make_button(registry, "Controls", goto_controls, menu_action::goto_controls, 9));
  b.push_back(make_button(registry, "Quit", quit, menu_action::quit, 11));
  // clang-format on
}

}  // namespace

auto create_home_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Wanderer", menu_id::home);

  add_buttons(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_in_game});

  return entity;
}

}  // namespace wanderer::sys
