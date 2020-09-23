#include "game.hpp"

#include <cassert>

#include "add_humanoid_state_dependencies.hpp"
#include "animation_system.hpp"
#include "component/tilemap.hpp"
#include "event_connections.hpp"
#include "ground_layer_rendering_system.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_factory_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "interpolation_system.hpp"
#include "make_map.hpp"
#include "make_viewport_system.hpp"
#include "movable_depth_drawables_system.hpp"
#include "movement_system.hpp"
#include "render_bounds_system.hpp"
#include "render_depth_drawables_system.hpp"
#include "tile_animation_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

Game::Game(cen::renderer& renderer)
{
  add_humanoid_state_dependencies(m_registry);
  connect_events(m_dispatcher);

  m_world = make_map(
      m_registry, "resource/map/world_demo.json", renderer, m_imageCache);

  m_player = sys::humanoid::add_player(m_registry, renderer, m_imageCache);
  m_viewport = sys::viewport::make_viewport(m_registry);

  sys::humanoid::add_skeleton(m_registry, renderer, m_imageCache);

  auto& view = m_registry.get<comp::viewport>(m_viewport.get());
  auto& level = m_registry.get<comp::tilemap>(m_world.get());

  view.levelSize.width = level.width;
  view.levelSize.height = level.height;
}

Game::~Game() noexcept
{
  disconnect_events(m_dispatcher);
}

void Game::handle_input(const Input& input)
{
  sys::input::update(m_registry, m_dispatcher, m_player, input);
}

void Game::tick(const delta dt)
{
  // TODO check if menu is blocking
  m_dispatcher.update();

  sys::humanoid::update_state(m_registry, m_dispatcher);
  sys::humanoid::update_animation(m_registry);
  sys::tile::update_animation(m_registry, m_world.get());  // FIXME m_world

  sys::update_movement(m_registry, dt);

  sys::update_animation_state(m_registry);
  // TODO need to update viewport level size as well when level changes
  sys::viewport::update(m_registry, m_viewport, m_player, dt);
}

void Game::render(cen::renderer& renderer, const alpha alpha)
{
  sys::viewport::translate(m_registry, m_viewport, renderer);

  sys::update_interpolation(m_registry, alpha);
  sys::update_movable_depth_drawables(m_registry);

  // FIXME m_world
  const auto& tilemap = m_registry.get<comp::tilemap>(m_world.get());
  const auto bounds = sys::calculate_render_bounds(
      m_registry, m_viewport, tilemap.rows, tilemap.cols);

  // TODO future optimization, only render tile object DepthDrawables in bounds
  //  {
  //    for (int r = bounds.minRow; r < bounds.maxRow; ++r) {
  //      for (int c = bounds.minCol; c < bounds.maxCol; ++c) {
  //        if (const auto& iter = tilemap.tileObjects.find(MapPosition{r, c});
  //            iter != tilemap.tileObjects.end()) {
  //          m_registry.emplace_or_replace<InBounds>(iter->second);
  //        }
  //      }
  //    }
  //  }

  sys::layer::render_ground(m_registry, m_world, renderer, bounds);

  // TODO render more stuff (think about render depth as well)
  sys::render_depth_drawables(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
