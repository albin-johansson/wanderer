#include "wanderer_game.hpp"

#include <centurion.hpp>

#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/events/player_events.hpp"
#include "wanderer/io/level-parsing/parse_levels.hpp"
#include "wanderer/meta/build.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"
#include "wanderer/systems/animation_system.hpp"
#include "wanderer/systems/cinematic_system.hpp"
#include "wanderer/systems/input_system.hpp"
#include "wanderer/systems/physics_system.hpp"
#include "wanderer/systems/registry_system.hpp"
#include "wanderer/systems/rendering_system.hpp"
#include "wanderer/systems/tile_system.hpp"
#include "wanderer/systems/ui_system.hpp"
#include "wanderer/systems/viewport_system.hpp"

namespace wanderer {

wanderer_game::wanderer_game(const game_cfg& cfg)
    : mCfg{cfg}
    , mSettings{load_settings()}
    , mGraphics{mCfg, mSettings}
    , mMainRegistry{sys::make_main_registry(mCfg)}
{
  debug("Logical size is {}", cfg.logical_size_f);

  using self = wanderer_game;
  mDispatcher.sink<action_event>().connect<&self::on_action>(this);
  mDispatcher.sink<move_player_event>().connect<&self::on_move_player>(this);
  mDispatcher.sink<stop_player_event>().connect<&self::on_stop_player>(this);

  parse_levels(mMainRegistry, mGraphics);

  /* Make sure that we can render the background */
  auto& registry = current_registry();
  sys::update_render_bounds(registry);
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

    /* Little optimization that avoids sorting too often, since the difference between
       sorting every tick versus every fourth tick is not really noticeable by the player.
       Example: 60Hz -> 0.0167s per tick -> 4 ticks/sort -> 0.067s in between sorts */
    if (static uint64 ticker = 0; ticker % 4 == 0) {
      sys::sort_drawables(registry, sys::sort_strategy::insertion);
      ++ticker;
    }

    sys::update_lights(registry);
    sys::update_animations(registry);
    sys::update_physics(registry, dt);
  }
}

void wanderer_game::render()
{
  auto& renderer = mGraphics.renderer();
  renderer.clear_with(cen::colors::black);

  const auto& registry = current_registry();
  sys::render_tiles(registry, mGraphics);
  sys::render_drawables(registry, mGraphics);
  sys::render_lights(registry, mGraphics);

  if constexpr (is_debug_build) {
    sys::debug_physics(registry, mGraphics);
  }

  sys::init_text_labels(mMainRegistry, mGraphics);
  sys::render_active_menu(mMainRegistry, mGraphics, mSettings);
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
    case action_id::toggle_vsync: {
      const bool enabled = mGraphics.toggle_vsync();
      mSettings.set_flag(settings::vsync_bit, enabled);
      break;
    }
    case action_id::toggle_integer_scaling: {
      const bool enabled = mGraphics.toggle_integer_scaling();
      mSettings.set_flag(settings::integer_scaling_bit, enabled);
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