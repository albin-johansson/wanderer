#include "game.hpp"

#include "common/milliseconds.hpp"
#include "components/ctx/renderer_snapshot.hpp"
#include "components/ctx/settings.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/event_connections.hpp"
#include "core/ecs/make_dispatcher.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/load_game_event.hpp"
#include "events/menu_events.hpp"
#include "io/saves/delete_save.hpp"
#include "io/saves/load_game.hpp"
#include "io/saves/save_game.hpp"
#include "systems/ai/chase_system.hpp"
#include "systems/ai/roam_system.hpp"
#include "systems/configuration/load_binds_system.hpp"
#include "systems/configuration/settings_system.hpp"
#include "systems/gfx/animation_system.hpp"
#include "systems/gfx/custom_animation_system.hpp"
#include "systems/gfx/debug_rendering_system.hpp"
#include "systems/gfx/depth_system.hpp"
#include "systems/gfx/drawable_system.hpp"
#include "systems/gfx/light_system.hpp"
#include "systems/gfx/render_bounds_system.hpp"
#include "systems/gfx/viewport_system.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/humanoid/humanoid_state_system.hpp"
#include "systems/input/input_system.hpp"
#include "systems/layers/tile_layer_rendering_system.hpp"
#include "systems/levels/io/load_levels.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/physics/movement_system.hpp"
#include "systems/physics/particle_system.hpp"
#include "systems/plant_system.hpp"
#include "systems/registry/shared_registry_factory_system.hpp"
#include "systems/tiles/tile_animation_system.hpp"
#include "systems/tiles/tile_object_animation_system.hpp"
#include "systems/time_system.hpp"
#include "systems/trigger_system.hpp"
#include "systems/ui/fps_system.hpp"
#include "systems/ui/hud/hud_rendering_system.hpp"
#include "systems/ui/hud/level_switch_animation_system.hpp"
#include "systems/ui/menus/menu_rendering_system.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"
#include "systems/ui/menus/settings/settings_menu_system.hpp"

namespace wanderer {

game::game(graphics_type& graphics)
    : m_shared{sys::make_shared_registry()}
    , m_dispatcher{make_dispatcher()}
{
  sys::load_levels(m_shared, graphics);

  // clang-format off
  m_dispatcher.sink<switch_map_event>().connect<&game::on_switch_map>(this);
  m_dispatcher.sink<switch_menu_event>().connect<&game::on_switch_menu>(this);
  m_dispatcher.sink<menu_switched_event>().connect<&game::on_menu_switched>(this);
  m_dispatcher.sink<button_pressed_event>().connect<&game::on_button_pressed>(this);

  m_dispatcher.sink<show_inventory_event>().connect<&game::on_show_inventory>(this);
  m_dispatcher.sink<close_inventory_event>().connect<&game::on_close_inventory>(this);

  m_dispatcher.sink<sleep_event>().connect<&game::on_sleep>(this);
  m_dispatcher.sink<day_changed_event>().connect<&game::on_day_changed>(this);

  m_dispatcher.sink<custom_animation_halfway_event>().connect<&game::on_custom_animation_halfway>(this);

  m_dispatcher.sink<spawn_particles_event>().connect<&game::on_spawn_particles>(this);
  m_dispatcher.sink<quit_event>().connect<&game::on_quit>(this);
  // clang-format on
}

game::~game()
{
  disconnect_events(m_dispatcher);
  m_dispatcher.disconnect(this);
}

void game::on_start()
{
  sys::load_settings(m_shared);
  m_shared.set<ctx::binds>(sys::load_binds());
  m_shared.ctx<ctx::time_of_day>().seconds = sys::hour_to_seconds(12);

  {
    auto& data = m_shared.emplace<comp::fps_data>(m_shared.create());
    data.then = cen::counter::ticks();
    data.interval = ms_t{500};
    data.next_update = data.then + data.interval;
  }

  const auto& settings = m_shared.ctx<ctx::settings>();
  m_dispatcher.enqueue<fullscreen_toggled_event>(settings.fullscreen);
  m_dispatcher.enqueue<integer_scaling_toggled_event>(settings.integer_scaling);

  sys::sync_settings_menu(m_shared);
  m_dispatcher.update();
}

void game::on_exit()
{
  sys::save_settings_before_exit(m_shared);
}

void game::handle_input(const rune::input& input)
{
  m_mousePos = input.mouse.position();
  sys::update_menu(m_shared, m_dispatcher, input);

  auto& level = sys::current_level(m_shared);
  sys::update_input(level.registry, m_dispatcher, input, m_shared.ctx<ctx::binds>());
}

void game::tick(const float dt)
{
  m_dispatcher.update();

  auto& level = sys::current_level(m_shared);
  sys::update_fps(m_shared, dt);

  sys::update_render_bounds(level.registry);
  sys::update_custom_animations(level.registry, m_dispatcher, dt);

  if (is_paused()) {
    return;
  }

  sys::update_time(m_shared, m_dispatcher, dt);
  sys::update_humanoid_states(level.registry, m_dispatcher);

  sys::update_chase(level.registry, m_dispatcher);
  sys::update_roaming(level.registry, dt);
  sys::update_movement(level.registry, level.tree, dt);
  sys::update_drawables(level.registry);
  sys::update_particles(level.registry, dt);
  sys::update_plants(level.registry, dt);
  sys::update_lights(level.registry);
  sys::update_player_light_position(level.registry);
  sys::update_triggers(level.registry, m_dispatcher);

  {
    const auto player = singleton_entity<comp::player>(level.registry);
    sys::update_viewport(level.registry, comp::movable::entity{player}, dt);
  }
  sys::sort_depth_drawables(level.registry);

  sys::update_animations(level.registry);
  sys::update_humanoid_animations(level.registry);
  sys::update_tile_animations(level.registry);
  sys::update_tile_object_animations(level.registry);
}

void game::render(graphics_type& graphics) const
{
  auto& renderer = graphics.get_renderer();
  auto& level = sys::current_level(m_shared);

  renderer.clear_with(cen::colors::black);

  sys::translate_viewport(level.registry, renderer);
  // sys::update_render_bounds(level.registry);

  sys::render_tile_layers(level.registry, graphics);
  sys::render_drawables(level.registry, graphics);
  sys::render_particles(level.registry, graphics);

  if (sys::is_current_level_outside(m_shared)) {
    sys::render_lights(level.registry,
                       graphics,
                       m_shared.ctx<ctx::time_of_day>(),
                       m_shared.ctx<ctx::settings>());
  }

  sys::render_clock(m_shared, graphics);

  if (m_updateSnapshot) {
    m_shared.set<ctx::renderer_snapshot>(renderer.capture(graphics.format()));
    m_updateSnapshot = false;
  }

  if constexpr (cen::is_debug_build()) {
    sys::render_debug_info(level.registry, graphics);
  }

  sys::render_hud(m_shared, graphics, m_mousePos);

  sys::render_active_menu(m_shared, graphics);
  sys::render_custom_animations(level.registry, graphics);

  sys::render_fps(m_shared, graphics);

  if constexpr (cen::is_debug_build()) {
    sys::render_menu_debug_info(m_shared, graphics);
  }

  renderer.present();
}

void game::load_save(const std::string& name, graphics_type& graphics)
{
  load_game(m_shared, graphics, name);

  auto& level = sys::current_level(m_shared);
  sys::start_bond_animation(level.registry, glob::load_game_id);
}

auto game::is_paused() const -> bool
{
  return sys::is_current_menu_blocking(m_shared);
}

void game::on_button_pressed(const button_pressed_event& event)
{
  switch (event.action) {
    default:
      [[fallthrough]];
    case menu_action::none:
      break;

    case menu_action::goto_in_game: {
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);
      break;
    }
    case menu_action::goto_home: {
      m_updateSnapshot = true;
      m_dispatcher.enqueue<switch_menu_event>(menu_id::home);
      break;
    }
    case menu_action::goto_controls: {
      m_dispatcher.enqueue<switch_menu_event>(menu_id::controls);
      break;
    }
    case menu_action::goto_settings: {
      m_dispatcher.enqueue<switch_menu_event>(menu_id::settings);
      break;
    }
    case menu_action::goto_saves: {
      m_dispatcher.enqueue<switch_menu_event>(menu_id::saves);
      break;
    }
    case menu_action::quick_save: {
      // FIXME don't allow quick saves before the in-game menu has been active once
      if (const auto* snapshot = m_shared.try_ctx<ctx::renderer_snapshot>()) {
        save_game("quick_save", m_shared, snapshot->surface);
      }
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);
      break;
    }
    case menu_action::load_game: {
      m_dispatcher.enqueue<load_game_event>(sys::get_selected_save_name(m_shared));
      break;
    }
    case menu_action::delete_game: {
      const auto name = sys::get_selected_save_name(m_shared);
      sys::remove_save_entry(m_shared, name);
      break;
    }
    case menu_action::change_save_preview: {
      sys::change_save_preview(m_shared);
      break;
    }
    case menu_action::decrement_saves_button_group_page: {
      sys::decrement_saves_button_group_page(m_shared);
      break;
    }
    case menu_action::increment_saves_button_group_page: {
      sys::increment_saves_button_group_page(m_shared);
      break;
    }
    case menu_action::toggle_fullscreen: {
      const auto enabled = sys::toggle_fullscreen(m_shared);
      m_dispatcher.enqueue<fullscreen_toggled_event>(enabled);
      break;
    }
    case menu_action::toggle_integer_scaling: {
      const auto enabled = sys::toggle_integer_scaling(m_shared);
      m_dispatcher.enqueue<integer_scaling_toggled_event>(enabled);
      break;
    }
    case menu_action::quit: {
      m_dispatcher.enqueue<quit_event>();
      break;
    }
  }
}

void game::on_switch_map(const switch_map_event& event)
{
  auto& level = sys::current_level(m_shared);
  sys::start_level_change_animation(level.registry, event.map);
}

void game::on_switch_menu(const switch_menu_event& event)
{
  sys::switch_menu(m_shared, m_dispatcher, event.id);
}

void game::on_menu_switched(const menu_switched_event& event)
{
  const auto& menu = m_shared.get<comp::menu>(event.entity);
  if (menu.id == menu_id::saves) {
    sys::refresh_saves_menu(m_shared);
  }
}

void game::on_custom_animation_halfway(const custom_animation_halfway_event& event)
{
  switch (event.id) {
    case glob::sleep_id:
      sys::change_to_next_day(m_shared, m_dispatcher, glob::morning_hour);
      break;

    case glob::load_game_id:
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);
      break;

    case glob::switch_level_id:
      const auto next = sys::prepare_current_level_before_switch(m_shared, event);
      sys::enable_level(m_shared, next);

      auto& level = sys::current_level(m_shared);
      sys::start_reverse_only_bond_animation(level.registry);

      break;
  }
}

void game::on_show_inventory(const show_inventory_event& event)
{
  auto& level = sys::current_level(m_shared);
  level.registry.emplace<comp::active_inventory>(event.inventory_entity);
}

void game::on_close_inventory(const close_inventory_event&)
{
  sys::current_level(m_shared).registry.clear<comp::active_inventory>();
}

void game::on_sleep(const sleep_event&)
{
  auto& level = sys::current_level(m_shared);
  sys::start_bond_animation(level.registry, glob::sleep_id);
}

void game::on_day_changed(const day_changed_event& event)
{
  // TODO update the state of plants, etc.
}

void game::on_spawn_particles(const spawn_particles_event& event)
{
  auto& level = sys::current_level(m_shared);
  sys::spawn_particles(level.registry,
                       event.position,
                       event.count,
                       event.duration,
                       event.color);
}

void game::on_quit(const quit_event&)
{
  if (const auto* snapshot = m_shared.try_ctx<ctx::renderer_snapshot>()) {
    create_exit_save(m_shared, snapshot->surface);
  }

  m_quit = true;
}

}  // namespace wanderer
