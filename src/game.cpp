#include "game.hpp"

#include "animation_system.hpp"
#include "button.hpp"
#include "chase_system.hpp"
#include "debug_rendering_system.hpp"
#include "depth_system.hpp"
#include "drawable_system.hpp"
#include "event_connections.hpp"
#include "fullscreen_toggled_event.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "integer_scaling_toggled_event.hpp"
#include "inventory_system.hpp"
#include "layer_system.hpp"
#include "level_switch_animation.hpp"
#include "level_switch_animation_system.hpp"
#include "light_system.hpp"
#include "load_binds_system.hpp"
#include "make_dispatcher.hpp"
#include "menu_system.hpp"
#include "movement_system.hpp"
#include "outside_level.hpp"
#include "particle_system.hpp"
#include "portal_system.hpp"
#include "settings.hpp"
#include "settings_system.hpp"
#include "tile_animation_system.hpp"
#include "tile_object_animation_system.hpp"
#include "time_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

game::game(graphics_context& graphics)
    : m_dispatcher{make_dispatcher()}
    , m_levels{graphics}
    , m_shared{sys::create_menus()}
{
  // clang-format off
  m_dispatcher.sink<event::switch_map>().connect<&game::on_switch_map>(this);
  m_dispatcher.sink<event::switch_menu>().connect<&game::on_switch_menu_event>(this);
  m_dispatcher.sink<event::button_pressed>().connect<&game::on_button_pressed>(this);
  m_dispatcher.sink<event::show_inventory_event>().connect<&game::on_show_inventory>(this);
  m_dispatcher.sink<event::close_inventory>().connect<&game::on_close_inventory>(this);
  m_dispatcher.sink<event::level_faded_in>().connect<&game::on_level_animation_faded_in>(this);
  m_dispatcher.sink<event::level_faded_out>().connect<&game::on_level_animation_faded_out>(this);
  m_dispatcher.sink<event::spawn_particles>().connect<&game::on_particle_event>(this);
  m_dispatcher.sink<event::quit_event>().connect<&game::on_quit_event>(this);
  // clang-format on
}

game::~game() noexcept
{
  disconnect_events(m_dispatcher);
  m_dispatcher.disconnect(this);
}

void game::handle_input(const input& input)
{
  auto* level = m_levels.current();
  sys::update_menu(m_shared, m_dispatcher, input);

  const auto& binds = m_shared.ctx<ctx::binds>();
  sys::update_input(level->registry(), m_dispatcher, input, binds);
}

void game::tick(const delta_t dt)
{
  m_dispatcher.update();

  if (is_paused())
  {
    return;
  }

  sys::update_time(m_shared, dt);

  auto* level = m_levels.current();
  auto& registry = level->registry();
  sys::update_humanoid_states(registry, m_dispatcher);

  sys::update_chase(registry, m_dispatcher);
  sys::update_movement(*level, dt);
  sys::update_drawables(registry);
  sys::update_particles(registry, dt);
  sys::update_lights(registry);
  sys::update_player_light_position(registry);

  sys::update_portal_triggers(registry);
  sys::update_inventory_triggers(registry);
  sys::update_viewport(*level, registry.ctx<ctx::player>().entity, dt);
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

  auto* level = m_levels.current();
  const auto& registry = level->registry();

  sys::translate_viewport(registry, renderer);
  level->update_render_bounds();

  sys::render_ground_layers(registry, graphics);
  sys::render_drawables(registry, graphics);
  sys::render_particles(registry, renderer);

  if (registry.try_ctx<ctx::outside_level>())
  {
    sys::render_lights(registry, m_shared.ctx<ctx::time_of_day>(), graphics);
  }

  sys::render_clock(m_shared, graphics);

  if constexpr (cen::is_debug_build())
  {
    sys::render_debug_info(registry, graphics);
  }

  sys::render_inventory(registry, renderer, mousePos);
  sys::render_level_switch_animations(registry, renderer);
  sys::render_menu(m_shared, renderer);

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
  m_dispatcher.enqueue<event::fullscreen_toggled>(settings.fullscreen);
  m_dispatcher.enqueue<event::integer_scaling_toggled>(settings.integerScaling);

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

void game::on_switch_map(const event::switch_map& event)
{
  sys::start_level_fade_animation(m_levels.registry(), event.map);
}

void game::on_switch_menu_event(const event::switch_menu& event)
{
  sys::switch_menu(m_shared, event.id);
}

void game::on_button_pressed(const event::button_pressed& event)
{
  switch (event.action)
  {
    case menu_action::none:
      break;

    case menu_action::goto_in_game: {
      m_dispatcher.enqueue<event::switch_menu>(menu_id::in_game);
      break;
    }
    case menu_action::goto_home: {
      m_dispatcher.enqueue<event::switch_menu>(menu_id::home);
      break;
    }
    case menu_action::goto_controls: {
      m_dispatcher.enqueue<event::switch_menu>(menu_id::controls);
      break;
    }
    case menu_action::goto_settings: {
      m_dispatcher.enqueue<event::switch_menu>(menu_id::settings);
      break;
    }
    case menu_action::goto_saves: {
      m_dispatcher.enqueue<event::switch_menu>(menu_id::saves);
      break;
    }
    case menu_action::quit: {
      m_dispatcher.enqueue<event::quit_event>();
      break;
    }
    case menu_action::toggle_fullscreen: {
      const auto enabled = sys::toggle_fullscreen(m_shared);
      m_dispatcher.enqueue<event::fullscreen_toggled>(enabled);
      break;
    }
    case menu_action::toggle_integer_scaling: {
      const auto enabled = sys::toggle_integer_scaling(m_shared);
      m_dispatcher.enqueue<event::integer_scaling_toggled>(enabled);
      break;
    }
    case menu_action::toggle_lights: {
      sys::toggle_simulate_lights(m_shared);
      break;
    }
  }
}

void game::on_level_animation_faded_in(const event::level_faded_in& event)
{
  m_levels.switch_to(event.map);
  sys::end_level_fade_animation(m_levels.registry(), event);
}

void game::on_level_animation_faded_out(event::level_faded_out)
{
  m_levels.clear<comp::level_switch_animation>();
}

void game::on_show_inventory(const event::show_inventory_event& event)
{
  m_levels.emplace<comp::active_inventory>(event.inventoryEntity);
}

void game::on_close_inventory(event::close_inventory)
{
  m_levels.clear<comp::active_inventory>();
}

void game::on_particle_event(const event::spawn_particles& event)
{
  for (auto i = 0; i < event.count; ++i)
  {
    sys::add_particle(m_levels.registry(), event.position, event.baseColor, event.nTicks);
  }
}

void game::on_quit_event(event::quit_event)
{
  m_quit = true;
}

}  // namespace wanderer
