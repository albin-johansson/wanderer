#include "game.hpp"

#include "components/ctx/outside_level.hpp"
#include "components/ctx/renderer_snapshot.hpp"
#include "components/ctx/settings.hpp"
#include "components/graphics/level_switch_animation.hpp"
#include "components/ui/button.hpp"
#include "components/ui/button_group.hpp"
#include "core/ecs/event_connections.hpp"
#include "core/ecs/make_dispatcher.hpp"
#include "events/fullscreen_toggled_event.hpp"
#include "events/integer_scaling_toggled_event.hpp"
#include "io/saves/save_game.hpp"
#include "systems/ai/chase_system.hpp"
#include "systems/configuration/load_binds_system.hpp"
#include "systems/configuration/settings_system.hpp"
#include "systems/graphics/animation_system.hpp"
#include "systems/graphics/debug_rendering_system.hpp"
#include "systems/graphics/depth_system.hpp"
#include "systems/graphics/drawable_system.hpp"
#include "systems/graphics/light_system.hpp"
#include "systems/graphics/particle_system.hpp"
#include "systems/graphics/tile_animation_system.hpp"
#include "systems/graphics/tile_layer_rendering_system.hpp"
#include "systems/graphics/tile_object_animation_system.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/humanoid/humanoid_state_system.hpp"
#include "systems/input/input_system.hpp"
#include "systems/inventory_system.hpp"
#include "systems/movement/movement_system.hpp"
#include "systems/movement/portal_system.hpp"
#include "systems/shared_registry_factory_system.hpp"
#include "systems/tile_layer_system.hpp"
#include "systems/time_system.hpp"
#include "systems/ui/hud/level_switch_animation_system.hpp"
#include "systems/ui/menus/menu_factory_system.hpp"
#include "systems/ui/menus/menu_rendering_system.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"
#include "systems/ui/menus/settings/settings_menu_system.hpp"

namespace wanderer {

game::game(graphics_context& graphics)
    : m_dispatcher{make_dispatcher()}
    , m_levels{graphics}
    , m_shared{sys::make_shared_registry()}
{
  // clang-format off
  m_dispatcher.sink<switch_map_event>().connect<&game::on_switch_map>(this);
  m_dispatcher.sink<switch_menu_event>().connect<&game::on_switch_menu_event>(this);
  m_dispatcher.sink<button_pressed_event>().connect<&game::on_button_pressed>(this);
  m_dispatcher.sink<show_inventory_event>().connect<&game::on_show_inventory>(this);
  m_dispatcher.sink<close_inventory_event>().connect<&game::on_close_inventory>(this);
  m_dispatcher.sink<level_faded_in_event>().connect<&game::on_level_animation_faded_in>(this);
  m_dispatcher.sink<level_faded_out_event>().connect<&game::on_level_animation_faded_out>(this);
  m_dispatcher.sink<spawn_particles_event>().connect<&game::on_particle_event>(this);
  m_dispatcher.sink<quit_event>().connect<&game::on_quit_event>(this);
  // clang-format on
}

game::~game()
{
  disconnect_events(m_dispatcher);
  m_dispatcher.disconnect(this);
}

void game::handle_input(const input& input)
{
  sys::update_menu(m_shared, m_dispatcher, input);
  sys::update_input(m_levels.registry(), m_dispatcher, input, m_shared.ctx<ctx::binds>());
}

void game::tick(const delta_time dt)
{
  m_dispatcher.update();

  if (is_paused())
  {
    return;
  }

  sys::update_time(m_shared, dt);

  auto& level = m_levels.current();
  auto& registry = level.registry();
  sys::update_humanoid_states(registry, m_dispatcher);

  sys::update_chase(registry, m_dispatcher);
  sys::update_movement(registry, level.tree(), dt);
  sys::update_drawables(registry);
  sys::update_particles(registry, dt);
  sys::update_lights(registry);
  sys::update_player_light_position(registry);

  sys::update_portal_triggers(registry);
  sys::update_inventory_triggers(registry);

  const auto player = registry.ctx<ctx::player>().entity;
  sys::update_viewport(registry, comp::movable::entity{player}, dt);
  sys::update_depth(registry);

  sys::update_animations(registry);
  sys::update_humanoid_animations(registry);
  sys::update_tile_animations(registry);
  sys::update_tile_object_animations(registry);
  sys::update_level_switch_animations(registry, m_dispatcher, dt);
}

void game::render(graphics_context& graphics, const cen::ipoint mousePos)
{
  auto& renderer = graphics.renderer();

  auto& level = m_levels.current();
  const auto& registry = level.registry();

  sys::translate_viewport(registry, renderer);
  level.update_render_bounds();

  sys::render_tile_layers(registry, graphics);
  sys::render_drawables(registry, graphics);
  sys::render_particles(registry, graphics);

  if (registry.try_ctx<const ctx::outside_level>())
  {
    sys::render_lights(registry,
                       graphics,
                       m_shared.ctx<ctx::time_of_day>(),
                       m_shared.ctx<ctx::settings>());
  }

  sys::render_clock(m_shared, graphics);

  if (m_updateSnapshot)
  {
    m_shared.set<ctx::renderer_snapshot>(renderer.capture(graphics.pixel_format()));
    m_updateSnapshot = false;
  }

  if constexpr (cen::is_debug_build())
  {
    sys::render_debug_info(registry, graphics);
  }

  sys::render_inventory(registry, renderer, mousePos);
  sys::render_level_switch_animations(registry, renderer);
  sys::render_active_menu(m_shared, graphics);

  if constexpr (cen::is_debug_build())
  {
    sys::render_menu_debug_info(m_shared, graphics);
  }
}

void game::on_start()
{
  sys::load_settings(m_shared);
  m_shared.set<ctx::binds>(sys::load_binds());
  m_shared.ctx<ctx::time_of_day>().seconds = 43'200;  // Start at 12:00

  const auto& settings = m_shared.ctx<ctx::settings>();
  m_dispatcher.enqueue<fullscreen_toggled_event>(settings.fullscreen);
  m_dispatcher.enqueue<integer_scaling_toggled_event>(settings.integerScaling);

  sys::sync_settings_menu(m_shared);
  m_dispatcher.update();
}

void game::on_exit()
{
  sys::save_settings_before_exit(m_shared);
}

auto game::is_paused() const -> bool
{
  return sys::is_current_menu_blocking(m_shared);
}

auto game::is_inventory_active() const -> bool
{
  return !is_paused() &&
         !m_levels.registry().view<const comp::active_inventory>().empty();
}

void game::on_switch_map(const switch_map_event& event)
{
  sys::start_level_fade_animation(m_levels.registry(), event.map);
}

void game::on_switch_menu_event(const switch_menu_event& event)
{
  sys::switch_menu(m_shared, event.id);
}

void game::on_button_pressed(const button_pressed_event& event)
{
  switch (event.action)
  {
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
      const auto& snapshot = m_shared.ctx<ctx::renderer_snapshot>();
      save_game("quick_save", m_levels, snapshot.surface);
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);
      break;
    }
    case menu_action::load_game: {
      // TODO
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
    case menu_action::quit: {
      m_dispatcher.enqueue<quit_event>();
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
    case menu_action::toggle_lights: {
      sys::toggle_simulate_lights(m_shared);
      break;
    }
  }
}

void game::on_level_animation_faded_in(const level_faded_in_event& event)
{
  m_levels.switch_to(event.map);
  sys::end_level_fade_animation(m_levels.registry(), event);
}

void game::on_level_animation_faded_out(const level_faded_out_event&)
{
  m_levels.registry().clear<comp::level_switch_animation>();
}

void game::on_show_inventory(const show_inventory_event& event)
{
  m_levels.registry().emplace<comp::active_inventory>(event.inventoryEntity);
}

void game::on_close_inventory(const close_inventory_event&)
{
  m_levels.registry().clear<comp::active_inventory>();
}

void game::on_particle_event(const spawn_particles_event& event)
{
  sys::spawn_particles(m_levels.registry(),
                       event.position,
                       event.count,
                       event.duration,
                       event.color);
}

void game::on_quit_event(const quit_event&)
{
  m_quit = true;
}

}  // namespace wanderer
