#include "game.hpp"

#include "animation_system.hpp"
#include "depth_drawables_system.hpp"
#include "event_connections.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "inventory_system.hpp"
#include "layer_rendering_system.hpp"
#include "level_factory.hpp"
#include "level_switch_animation.hpp"
#include "level_switch_animation_system.hpp"
#include "make_dispatcher.hpp"
#include "movable.hpp"
#include "movement_system.hpp"
#include "portal_system.hpp"
#include "tile_animation_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

game::game(graphics_context& graphics)
    : m_dispatcher{make_dispatcher()}
    , m_levels{graphics}
{
  // clang-format off
  m_dispatcher.sink<comp::switch_map_event>().connect<&game::on_switch_map>(this);
  m_dispatcher.sink<comp::level_faded_in_event>().connect<&game::on_level_animation_faded_in>(this);
  m_dispatcher.sink<comp::level_faded_out_event>().connect<&game::on_level_animation_faded_out>(this);
  m_dispatcher.sink<comp::show_inventory_event>().connect<&game::on_show_inventory>(this);
  m_dispatcher.sink<comp::close_inventory_event>().connect<&game::on_close_inventory>(this);
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
  m_menus.update(mouseState, keyState, m_cursors);
  auto* level = m_levels.current();
  sys::input::update(level->registry(),
                     m_dispatcher,
                     level->player(),
                     keyState);
}

void game::tick(const delta_t dt)
{
  m_dispatcher.update();

  if (fully_paused()) {
    return;
  }

  auto* level = m_levels.current();
  auto& registry = level->registry();
  sys::humanoid::update_state(registry, m_dispatcher);

  if (!weakly_paused()) {
    sys::movement::update(*level, dt);
    sys::depthdrawable::update_movable(registry);

    sys::portal::update_triggers(registry, level->player());
    sys::inventory::update_triggers(registry, level->player());

    sys::animated::update(registry);
    sys::viewport::update(*level, level->player(), dt);

    sys::depthdrawable::sort(registry);
  }

  sys::humanoid::update_animation(registry);
  sys::tile::update_animation(registry);

  const auto& tileset = level->get<comp::tileset>(level->tileset());
  sys::depthdrawable::update_tile_animations(registry, tileset);

  sys::hud::update_level_switch_animations(registry, m_dispatcher);
}

void game::render(cen::renderer& renderer)
{
  auto* level = m_levels.current();
  auto& registry = level->registry();

  sys::viewport::translate(registry, level->viewport(), renderer);

  const auto bounds = level->get_render_bounds();
  sys::layer::render_ground(registry,
                            level->get<comp::tileset>(level->tileset()),
                            renderer,
                            bounds);
  sys::depthdrawable::render(registry, renderer, bounds);

  sys::inventory::render(registry, renderer);
  sys::hud::render_level_switch_animations(registry, renderer);

  if (m_menus.is_blocking()) {
    m_menus.render(renderer);
  }
}

auto game::fully_paused() const -> bool
{
  return m_menus.is_blocking();
}

auto game::weakly_paused() const -> bool
{
  const auto& registry = m_levels.current()->registry();
  return !fully_paused() &&
         !registry.view<const comp::active_inventory>().empty();
}

void game::on_switch_map(const comp::switch_map_event& event)
{
  auto* current = m_levels.current();
  sys::hud::start_level_fade_animation(current->registry(), event.map);
}

void game::on_level_animation_faded_in(const comp::level_faded_in_event& event)
{
  {
    auto* current = m_levels.current();
    auto& registry = current->registry();

    registry.clear<comp::level_switch_animation>();

    auto& movable = current->get<comp::movable>(current->player());
    movable.velocity.zero();

    sys::viewport::center_on(registry, current->viewport(), movable.position);
  }

  m_levels.switch_to(event.map);
  auto* current = m_levels.current();
  auto& registry = current->registry();
  sys::hud::end_level_fade_animation(registry, event);
}

void game::on_level_animation_faded_out(comp::level_faded_out_event)
{
  m_levels.current()->clear<comp::level_switch_animation>();
}

void game::on_show_inventory(const comp::show_inventory_event& event)
{
  m_levels.current()->emplace<comp::active_inventory>(event.inventoryEntity);
}

void game::on_close_inventory(comp::close_inventory_event)
{
  m_levels.current()->clear<comp::active_inventory>();
}

}  // namespace wanderer
