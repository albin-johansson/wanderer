#include "game.hpp"

#include "components/ctx/renderer_snapshot.hpp"
#include "components/ctx/settings.hpp"
#include "components/graphics/level_switch_animation.hpp"
#include "components/outside_level.hpp"
#include "core/ecs/event_connections.hpp"
#include "core/ecs/make_dispatcher.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/levels/load_levels.hpp"
#include "events/fullscreen_toggled_event.hpp"
#include "events/integer_scaling_toggled_event.hpp"
#include "events/load_game_event.hpp"
#include "io/saves/load_game.hpp"
#include "io/saves/save_game.hpp"
#include "systems/ai/chase_system.hpp"
#include "systems/ai/roam_system.hpp"
#include "systems/configuration/load_binds_system.hpp"
#include "systems/configuration/settings_system.hpp"
#include "systems/graphics/animation_system.hpp"
#include "systems/graphics/debug_rendering_system.hpp"
#include "systems/graphics/depth_system.hpp"
#include "systems/graphics/drawable_system.hpp"
#include "systems/graphics/light_system.hpp"
#include "systems/graphics/particle_system.hpp"
#include "systems/graphics/render_bounds_system.hpp"
#include "systems/graphics/tile_animation_system.hpp"
#include "systems/graphics/tile_layer_rendering_system.hpp"
#include "systems/graphics/tile_object_animation_system.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"
#include "systems/humanoid/humanoid_state_system.hpp"
#include "systems/input/input_system.hpp"
#include "systems/inventory_system.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/movement/movement_system.hpp"
#include "systems/movement/portal_system.hpp"
#include "systems/shared_registry_factory_system.hpp"
#include "systems/time_system.hpp"
#include "systems/ui/hud/hud_rendering_system.hpp"
#include "systems/ui/hud/level_switch_animation_system.hpp"
#include "systems/ui/menus/menu_rendering_system.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"
#include "systems/ui/menus/settings/settings_menu_system.hpp"

namespace wanderer {

game::game(graphics_context& graphics)
    : m_shared{sys::make_shared_registry()}
    , m_dispatcher{make_dispatcher()}
{
  load_levels(m_shared, graphics);

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

void game::on_start()
{
  sys::load_settings(m_shared);
  m_shared.set<ctx::binds>(sys::load_binds());
  m_shared.ctx<ctx::time_of_day>().seconds = 43'200;  // Start at 12:00

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

void game::tick(const rune::delta_time dt)
{
  m_dispatcher.update();

  if (is_paused())
  {
    return;
  }

  auto& level = sys::current_level(m_shared);

  sys::update_time(m_shared, dt);
  sys::update_humanoid_states(level.registry, m_dispatcher);

  sys::update_chase(level.registry, m_dispatcher);
  sys::update_roaming(level.registry, dt);
  sys::update_movement(level.registry, level.tree, dt);
  sys::update_drawables(level.registry);
  sys::update_particles(level.registry, dt);
  sys::update_lights(level.registry);
  sys::update_player_light_position(level.registry);

  sys::update_portal_triggers(level.registry);
  sys::update_inventory_triggers(level.registry);

  const auto player = singleton_entity<comp::player>(level.registry);
  sys::update_viewport(level.registry, comp::movable::entity{player}, dt);
  sys::update_depth(level.registry);

  sys::update_animations(level.registry);
  sys::update_humanoid_animations(level.registry);
  sys::update_tile_animations(level.registry);
  sys::update_tile_object_animations(level.registry);
  sys::update_level_switch_animations(level.registry, m_dispatcher, dt);
}

void game::render(graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  auto& level = sys::current_level(m_shared);

  sys::translate_viewport(level.registry, renderer);
  sys::update_render_bounds(level.registry);

  sys::render_tile_layers(level.registry, graphics);
  sys::render_drawables(level.registry, graphics);
  sys::render_particles(level.registry, graphics);

  if (sys::is_current_level_outside(m_shared))
  {
    sys::render_lights(level.registry,
                       graphics,
                       m_shared.ctx<ctx::time_of_day>(),
                       m_shared.ctx<ctx::settings>());
  }

  sys::render_clock(m_shared, graphics);

  if (m_updateSnapshot)
  {
    m_shared.set<ctx::renderer_snapshot>(renderer.capture(graphics.format()));
    m_updateSnapshot = false;
  }

  if constexpr (cen::is_debug_build())
  {
    sys::render_debug_info(level.registry, graphics);
  }

  sys::render_hud(m_shared, graphics);
  sys::render_inventory(level.registry, renderer, m_mousePos);

  sys::render_active_menu(m_shared, graphics);
  sys::render_level_switch_animations(level.registry, renderer);

  if constexpr (cen::is_debug_build())
  {
    sys::render_menu_debug_info(m_shared, graphics);
  }
}

void game::load_save(const std::string& name, graphics_context& graphics)
{
  load_game(m_shared, graphics, name);
}

auto game::is_paused() const -> bool
{
  return sys::is_current_menu_blocking(m_shared);
}

void game::on_switch_map(const switch_map_event& event)
{
  auto& level = sys::current_level(m_shared);
  sys::start_level_fade_animation(level.registry, event.map);
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
      if (const auto* snapshot = m_shared.try_ctx<ctx::renderer_snapshot>())
      {
        save_game("quick_save", m_shared, snapshot->surface);
      }
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);
      break;
    }
    case menu_action::load_game: {
      m_dispatcher.enqueue<load_game_event>(sys::get_selected_save_name(m_shared));
      m_dispatcher.enqueue<switch_menu_event>(menu_id::in_game);

      // TODO animation

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
  }
}

void game::on_level_animation_faded_in(const level_faded_in_event& event)
{
  {
    auto& currentLevel = sys::current_level(m_shared);
    currentLevel.registry.clear<comp::level_switch_animation>();

    const auto player = singleton_entity<comp::player>(currentLevel.registry);
    auto& movable = currentLevel.registry.get<comp::movable>(player);
    movable.velocity.reset();

    sys::center_viewport_on(currentLevel.registry, movable.position);

    m_shared.clear<comp::active_level>();
    for (auto&& [entity, level] : m_shared.view<comp::level>().each())
    {
      if (level.id == event.map)
      {
        m_shared.emplace<comp::active_level>(entity);
        break;
      }
    }
  }

  auto& level = sys::current_level(m_shared);
  sys::end_level_fade_animation(level.registry, event);
}

void game::on_level_animation_faded_out(const level_faded_out_event&)
{
  sys::current_level(m_shared).registry.clear<comp::level_switch_animation>();
}

void game::on_show_inventory(const show_inventory_event& event)
{
  auto& level = sys::current_level(m_shared);
  level.registry.emplace<comp::active_inventory>(event.inventoryEntity);
}

void game::on_close_inventory(const close_inventory_event&)
{
  sys::current_level(m_shared).registry.clear<comp::active_inventory>();
}

void game::on_particle_event(const spawn_particles_event& event)
{
  auto& level = sys::current_level(m_shared);
  sys::spawn_particles(level.registry,
                       event.position,
                       event.count,
                       event.duration,
                       event.color);
}

void game::on_quit_event(const quit_event&)
{
  if (const auto* snapshot = m_shared.try_ctx<ctx::renderer_snapshot>())
  {
    create_exit_save(m_shared, snapshot->surface);
  }

  m_quit = true;
}

}  // namespace wanderer
