#include "game.hpp"

#include "animation_system.hpp"
#include "depth_drawables_system.hpp"
#include "event_connections.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
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
  if (!m_menus.is_blocking()) {
    auto* level = m_levels.current();
    sys::input::update(level->registry(),
                       m_dispatcher,
                       level->player(),
                       keyState);
  }
}

void game::tick(const delta_t dt)
{
  if (!m_menus.is_blocking()) {
    m_dispatcher.update();

    auto* level = m_levels.current();
    auto& registry = level->registry();
    sys::humanoid::update_state(registry, m_dispatcher);

    sys::humanoid::update_animation(registry);
    sys::tile::update_animation(registry);

    sys::movement::update(*level, dt);
    sys::depthdrawable::update_movable(registry);
    sys::portal::update(registry, level->player());

    sys::animated::update(registry);
    sys::viewport::update(*level, level->player(), dt);
  }
}

void game::render(cen::renderer& renderer)
{
  auto* level = m_levels.current();

  auto& registry = level->registry();
  const auto& tileset = level->tileset_comp();

  sys::viewport::translate(registry, level->viewport(), renderer);

  sys::depthdrawable::sort(registry);
  sys::depthdrawable::update_tile_animations(registry, tileset);
  sys::hud::update_level_switch_animations(registry, m_dispatcher);

  const auto bounds = level->get_render_bounds();
  sys::layer::render_ground(registry, tileset, renderer, bounds);
  sys::depthdrawable::render(registry, renderer, bounds);
  sys::hud::render_level_switch_animations(registry, renderer);

  if (m_menus.is_blocking()) {
    m_menus.render(renderer);
  }
}

void game::on_switch_map(const comp::switch_map_event& event)
{
  auto* current = m_levels.current();
  auto& registry = current->registry();

  sys::hud::start_level_fade_animation(registry, event.map);
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
  m_levels.current()->registry().clear<comp::level_switch_animation>();
}

}  // namespace wanderer
