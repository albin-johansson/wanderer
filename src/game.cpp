#include "game.hpp"

#include "animation_system.hpp"
#include "event_connections.hpp"
#include "ground_layer_rendering_system.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_factory_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "make_dispatcher.hpp"
#include "make_map.hpp"
#include "make_viewport_system.hpp"
#include "movable_depth_drawables_system.hpp"
#include "movement_system.hpp"
#include "render_bounds_system.hpp"
#include "render_depth_drawables_system.hpp"
#include "tile_animation_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

game::game(cen::renderer& renderer)
    : m_dispatcher{make_dispatcher()},
      m_world{make_map(m_level.registry(),
                       "resource/map/world_demo.json",
                       renderer,
                       m_imageCache)},
      m_player{sys::humanoid::add_player(m_level, renderer, m_imageCache)},
      m_viewport{sys::viewport::make_viewport(m_level.registry())}
{
  sys::humanoid::add_skeleton(m_level, renderer, m_imageCache);

  auto& view = m_level.get<comp::viewport>(m_viewport.get());
  auto& level = m_level.get<comp::tilemap>(m_world.get());

  view.levelSize.width = level.width;
  view.levelSize.height = level.height;
}

game::~game() noexcept
{
  disconnect_events(m_dispatcher);
}

void game::handle_input(const cen::mouse_state& mouseState,
                        const cen::key_state& keyState)
{
  m_menus.update(mouseState, keyState);
  if (!m_menus.is_blocking()) {
    sys::input::update(m_level.registry(), m_dispatcher, m_player, keyState);
  }
}

void game::tick(delta dt)
{
  if (!m_menus.is_blocking()) {
    m_dispatcher.update();

    auto& registry = m_level.registry();

    sys::humanoid::update_state(registry, m_dispatcher);
    sys::humanoid::update_animation(registry);
    sys::tile::update_animation(registry);

    sys::update_movement(m_level, dt);
    sys::update_movable_depth_drawables(registry);
    sys::update_animation_state(registry);

    // TODO need to update viewport level size as well when level changes
    sys::viewport::update(registry, m_viewport, m_player, dt);
  }
}

void game::render(cen::renderer& renderer)
{
  auto& registry = m_level.registry();

  sys::viewport::translate(registry, m_viewport, renderer);

  // FIXME m_world
  const auto& tilemap = m_level.get<comp::tilemap>(m_world.get());

  const auto bounds = sys::calculate_render_bounds(
      registry, m_viewport, tilemap.rows, tilemap.cols);

  sys::layer::render_ground(registry, m_world, renderer, bounds);
  sys::render_depth_drawables(registry, renderer);

  // TODO render HUD

  if (m_menus.is_blocking()) {
    m_menus.render(renderer);
  }
}

}  // namespace wanderer
