#include "game.hpp"

#include "animation_system.hpp"
#include "chase_system.hpp"
#include "depth_drawables_system.hpp"
#include "event_connections.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "inventory_system.hpp"
#include "layer_rendering_system.hpp"
#include "level_switch_animation.hpp"
#include "level_switch_animation_system.hpp"
#include "make_dispatcher.hpp"
#include "menu_system.hpp"
#include "movement_system.hpp"
#include "particle_system.hpp"
#include "portal_system.hpp"
#include "settings_system.hpp"
#include "tile_animation_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

game::game(graphics_context& graphics)
    : m_dispatcher{make_dispatcher()}
    , m_levels{graphics}
    , m_menus{sys::create_menus()}
{
  sys::load_settings(m_menus);

  // clang-format off
  m_dispatcher.sink<comp::switch_map_event>().connect<&game::on_switch_map>(this);
  m_dispatcher.sink<comp::switch_menu_event>().connect<&game::on_switch_menu_event>(this);
  m_dispatcher.sink<comp::button_pressed_event>().connect<&game::on_button_pressed>(this);
  m_dispatcher.sink<comp::show_inventory_event>().connect<&game::on_show_inventory>(this);
  m_dispatcher.sink<comp::close_inventory_event>().connect<&game::on_close_inventory>(this);
  m_dispatcher.sink<comp::level_faded_in_event>().connect<&game::on_level_animation_faded_in>(this);
  m_dispatcher.sink<comp::level_faded_out_event>().connect<&game::on_level_animation_faded_out>(this);
  m_dispatcher.sink<comp::particle_event>().connect<&game::on_particle_event>(this);
  m_dispatcher.sink<comp::quit_event>().connect<&game::on_quit_event>(this);
  // clang-format on
}

game::~game() noexcept
{
  disconnect_events(m_dispatcher);
  m_dispatcher.disconnect(this);
}

void game::handle_input(const cen::mouse_state& mouseState,
                        const cen::key_state& keyState)
{
  auto* level = m_levels.current();
  sys::update_menu(m_menus, m_dispatcher, mouseState, keyState);
  sys::update_input(level->registry(), m_dispatcher, level->player(), keyState);
}

void game::tick(const delta_t dt)
{
  m_dispatcher.update();

  if (is_paused())
  {
    return;
  }

  auto* level = m_levels.current();
  auto& registry = level->registry();
  sys::update_humanoid_states(registry, m_dispatcher);

  sys::update_chase(registry, m_dispatcher);
  sys::update_movement(*level, dt);
  sys::update_drawable_movables(registry);
  sys::update_particles(registry, dt);

  const auto player = level->player();
  sys::update_portal_triggers(registry, player);
  sys::update_inventory_triggers(registry, player);
  sys::update_viewport(*level, player, dt);
  sys::sort_drawables(registry);

  sys::update_animations(registry);
  sys::update_humanoid_animations(registry);
  sys::update_tile_animations(registry);
  sys::update_tile_object_animations(registry, level->tileset());
  sys::update_level_switch_animations(registry, m_dispatcher);
}

void game::render(graphics_context& graphics, const cen::ipoint mousePos)
{
  auto& renderer = graphics.renderer();

  const auto* level = m_levels.current();
  const auto& registry = level->registry();

  sys::translate_renderer_viewport(registry, level->viewport(), renderer);

  const auto bounds = level->get_render_bounds();
  sys::render_ground_layers(registry, level->tileset(), graphics, bounds);
  sys::render_drawables(registry, graphics, bounds);
  sys::render_particles(registry, renderer);
  sys::render_inventory(registry, renderer, mousePos);
  sys::render_level_switch_animations(registry, renderer);

  sys::render_menu(m_menus, renderer);
}

auto game::is_paused() const -> bool
{
  return sys::is_current_menu_blocking(m_menus);
}

auto game::is_inventory_active() const -> bool
{
  return !is_paused() &&
         !m_levels.registry().view<const comp::active_inventory>().empty();
}

void game::on_switch_map(const comp::switch_map_event& event)
{
  sys::start_level_fade_animation(m_levels.registry(), event.map);
}

void game::on_switch_menu_event(const comp::switch_menu_event& event)
{
  sys::switch_menu(m_menus, event.id);
}

void game::on_button_pressed(const comp::button_pressed_event& event)
{
}

void game::on_level_animation_faded_in(const comp::level_faded_in_event& event)
{
  m_levels.switch_to(event.map);
  sys::end_level_fade_animation(m_levels.registry(), event);
}

void game::on_level_animation_faded_out(comp::level_faded_out_event)
{
  m_levels.clear<comp::level_switch_animation>();
}

void game::on_show_inventory(const comp::show_inventory_event& event)
{
  m_levels.emplace<comp::active_inventory>(event.inventoryEntity);
}

void game::on_close_inventory(comp::close_inventory_event)
{
  m_levels.clear<comp::active_inventory>();
}

void game::on_particle_event(const comp::particle_event& event)
{
  for (auto i = 0; i < event.count; ++i)
  {
    sys::add_particle(m_levels.registry(),
                      event.position,
                      event.baseColor,
                      event.nTicks);
  }
}

void game::on_quit_event(comp::quit_event)
{
  m_quit = true;
}

}  // namespace wanderer
