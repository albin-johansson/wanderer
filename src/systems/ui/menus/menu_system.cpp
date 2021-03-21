#include "menu_system.hpp"

#include <centurion.hpp>

#include "button_system.hpp"
#include "cursors.hpp"
#include "home_menu_factory_system.hpp"
#include "menu.hpp"
#include "menu_rendering_system.hpp"
#include "parse_menu.hpp"
#include "saves_menu_system.hpp"
#include "settings_menu_system.hpp"
#include "switch_menu_event.hpp"

namespace wanderer::sys {
namespace {

void query_binds(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 comp::key_bind_pack& pack,
                 const cen::key_state& keys)
{
  for (const auto entity : pack.binds)
  {
    auto& bind = registry.get<comp::key_bind>(entity);
    if (keys.was_just_released(bind.key))
    {
      if (bind.action)
      {
        bind.action->execute(dispatcher);
      }
    }
  }
}

}  // namespace

auto create_menus() -> entt::registry
{
  entt::registry registry;

  const auto home = create_home_menu(registry);
  parse_menu(registry, "resources/menus/in_game_menu.json");
  parse_menu(registry, "resources/menus/controls_menu.json");

  create_settings_menu(registry);
  create_saves_menu(registry);

  registry.emplace<comp::active_menu>(home);

  auto& cursors = registry.emplace<comp::cursors>(registry.create());
  cursors.data.try_emplace(cen::system_cursor::hand, cen::system_cursor::hand);

  return registry;
}

void update_menu(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const cen::mouse_state& mouseState,
                 const cen::key_state& keyState)
{
  const auto view = registry.view<comp::active_menu, comp::menu>();
  view.each([&](const entt::entity entity, comp::menu& menu) {
    const auto menuEntity = comp::menu::entity{entity};

    const auto button = update_button_hover(registry, menuEntity, mouseState);
    if (button)
    {
      query_button(registry, dispatcher, *button, mouseState);
    }
    else
    {
      cen::cursor::reset();
    }

    if (auto* binds = registry.try_get<comp::key_bind_pack>(entity))
    {
      query_binds(registry, dispatcher, *binds, keyState);
    }
  });
}

void switch_menu(entt::registry& registry, const menu_id id)
{
  registry.clear<comp::active_menu>();

  const auto view = registry.view<comp::menu>();
  view.each([&](const entt::entity e, const comp::menu& menu) {
    if (menu.id == id)
    {
      registry.emplace<comp::active_menu>(e);

      if (menu.id == menu_id::saves)
      {
        refresh_saves_menu(registry);
      }
    }
  });
}

void render_menu(const entt::registry& registry, cen::renderer& renderer)
{
  render_active_menu(registry, renderer);
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto view = registry.view<const comp::active_menu, const comp::menu>();
  return view.get<const comp::menu>(view.front()).blocking;
}

}  // namespace wanderer::sys
