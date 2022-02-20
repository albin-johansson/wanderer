#include "wanderer_game.hpp"

#include <centurion.hpp>

#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/io/level-parsing/parse_levels.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/systems/registry_system.hpp"
#include "wanderer/systems/tile_system.hpp"
#include "wanderer/systems/ui_system.hpp"
#include "wanderer/systems/viewport_system.hpp"

namespace wanderer {

wanderer_game::wanderer_game()
    : mCfg{make_game_cfg()}
    , mGraphics{mCfg}
    , mMainRegistry{sys::make_main_registry()}
{
  mDispatcher.sink<action_event>().connect<&wanderer_game::on_action>(this);

  /* Make sure that we can render background */
  auto& registry = current_registry();
  sys::update_render_bounds(registry, mCfg);
}

void wanderer_game::run()
{
  auto& window = mGraphics.window();
  window.center();
  window.show();

  start();

  window.hide();
}

void wanderer_game::process_events()
{
  mInput.refresh(mGraphics.renderer());

  cen::event_handler event;

  while (event.poll()) {
    if (event.is(cen::event_type::quit)) {
      stop();
      break;
    }
    else if (event.is(cen::event_type::key_up)) {
      const auto& ke = event.get<cen::keyboard_event>();
      if (ke.is_active(cen::scancodes::q)) {
        stop();
        break;
      }
    }
  }

  sys::update_menus(mMainRegistry, mDispatcher, mInput);
}

void wanderer_game::update(const float32 dt)
{
  mDispatcher.update();

  //  if (static bool first = true; first) {
  //    sys::schedule_startup_cinematic_fade(mMainRegistry);
  //    first = false;
  //  }

  //  sys::update_cinematic_fade(mMainRegistry);

  if (!sys::is_current_menu_blocking(mMainRegistry)) {
    auto& registry = current_registry();
    sys::update_viewport(registry, dt);
    sys::update_render_bounds(registry, mCfg);
  }
}

void wanderer_game::render()
{
  const auto& registry = current_registry();

  auto& renderer = mGraphics.renderer();
  renderer.clear_with(cen::colors::black);

  sys::init_text_labels(registry, mGraphics);
  sys::init_text_labels(mMainRegistry, mGraphics);
  sys::render_tiles(registry, mCfg, mGraphics);
  sys::render_menus(mMainRegistry, mGraphics);

  //  sys::render_cinematic_fade(mMainRegistry, mGraphics);

  renderer.present();
}

void wanderer_game::on_action(const action_event& event)
{
  switch (event.action) {
    case action_id::noop:
      break;

    case action_id::quit:
      stop();
      break;

    case action_id::goto_game:
      sys::switch_menu(mMainRegistry, menu_id::game);
      break;

    case action_id::goto_main_menu:
      sys::switch_menu(mMainRegistry, menu_id::home);
      break;

    case action_id::goto_options_menu:
      sys::switch_menu(mMainRegistry, menu_id::options);
      break;

    case action_id::goto_saves_menu:
      sys::switch_menu(mMainRegistry, menu_id::saves);
      break;

    case action_id::goto_credits_menu:
      sys::switch_menu(mMainRegistry, menu_id::credits);
      break;

    case action_id::quick_save:
      // TODO
      break;

    case action_id::toggle_fullscreen:
      mGraphics.toggle_fullscreen();
      break;

    default:
      throw_traced(wanderer_error{"Invalid action!"});
  }
}

auto wanderer_game::current_registry() -> entt::registry&
{
  auto& levels = mMainRegistry.ctx<comp::level_ctx>();
  return levels.levels.at(levels.current);
}

}  // namespace wanderer