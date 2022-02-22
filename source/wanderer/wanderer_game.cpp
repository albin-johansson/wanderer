#include "wanderer_game.hpp"

#include <centurion.hpp>

#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/events/player_events.hpp"
#include "wanderer/io/level-parsing/parse_levels.hpp"
#include "wanderer/meta/build.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/systems/animation_system.hpp"
#include "wanderer/systems/cinematic_system.hpp"
#include "wanderer/systems/input_system.hpp"
#include "wanderer/systems/physics_system.hpp"
#include "wanderer/systems/registry_system.hpp"
#include "wanderer/systems/tile_system.hpp"
#include "wanderer/systems/ui_system.hpp"
#include "wanderer/systems/viewport_system.hpp"

namespace wanderer {

wanderer_game::wanderer_game()
    : mCfg{make_game_cfg()}
    , mSettings{load_settings()}
    , mGraphics{mCfg}
    , mMainRegistry{sys::make_main_registry(mCfg)}
{
  using self = wanderer_game;
  mDispatcher.sink<action_event>().connect<&self::on_action>(this);
  mDispatcher.sink<move_player_event>().connect<&self::on_move_player>(this);
  mDispatcher.sink<stop_player_event>().connect<&self::on_stop_player>(this);

  parse_levels(mMainRegistry, mGraphics);

  /* Make sure that we can render background */
  auto& registry = current_registry();
  sys::update_render_bounds(registry);

  mGraphics.set_fullscreen(mSettings.test_flag(settings::fullscreen_bit));
}

void wanderer_game::run()
{
  auto& window = mGraphics.window();
  window.center();
  window.show();

  start();

  save_settings(mSettings);
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
  }

  if (!sys::is_current_menu_blocking(mMainRegistry)) {
    sys::update_input(mDispatcher, mInput);
  }

  sys::update_menus(mMainRegistry, mDispatcher, mInput);
}

void wanderer_game::update(const float32 dt)
{
  mDispatcher.update();

  if (static bool first = true; first) {
    sys::schedule_startup_cinematic_fade(mMainRegistry);
    first = false;
  }

  sys::update_cinematic_fade(mMainRegistry);

  if (!sys::is_cinematic_fade_active(mMainRegistry) &&
      !sys::is_current_menu_blocking(mMainRegistry)) {
    auto& registry = current_registry();
    sys::update_viewport(registry, dt);
    sys::update_render_bounds(registry);

    sys::update_animations(registry);
    sys::update_movable_game_objects(registry, dt);
  }
}

void wanderer_game::render()
{
  const auto& registry = current_registry();

  auto& renderer = mGraphics.renderer();
  renderer.clear_with(cen::colors::black);

  sys::init_text_labels(mMainRegistry, mGraphics);

  sys::render_tiles(registry, mGraphics);

  sys::render_active_menu(mMainRegistry, mGraphics);
  sys::render_cinematic_fade(mMainRegistry, mGraphics);

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

    case action_id::toggle_fullscreen: {
      const bool enabled = mGraphics.toggle_fullscreen();

      if constexpr (on_osx) {
        if (!enabled) {
          mGraphics.window().center();
        }
      }

      mSettings.set_flag(settings::fullscreen_bit, enabled);
      break;
    }
    default:
      throw_traced(wanderer_error{"Invalid action!"});
  }
}

void wanderer_game::on_move_player(const move_player_event& event)
{
  auto& registry = current_registry();
  sys::on_move_player(registry, event);
}

void wanderer_game::on_stop_player(const stop_player_event& event)
{
  auto& registry = current_registry();
  sys::on_stop_player(registry, event);
}

auto wanderer_game::current_registry() -> entt::registry&
{
  auto& levels = mMainRegistry.ctx<comp::level_ctx>();
  return levels.levels.at(levels.current);
}

}  // namespace wanderer