#include "game.h"

#include <humanoid_state.h>

#include "animation_system.h"
#include "ground_layer_rendering_system.h"
#include "humanoid_animation_system.h"
#include "humanoid_factory_system.h"
#include "humanoid_state_system.h"
#include "input_system.h"
#include "interpolation_system.h"
#include "make_map.h"
#include "make_viewport.h"
#include "movement_system.h"
#include "render_bounds_system.h"
#include "render_movables_system.h"
#include "tile_animation_system.h"
#include "tilemap.h"
#include "translation_viewport_system.h"
#include "viewport_system.h"

using namespace wanderer::system;

using centurion::Renderer;

namespace wanderer {

Game::Game(Renderer& renderer)
    : m_player{humanoid::add_player(m_registry, renderer)},
      m_world{make_map(m_registry, "world_demo.json", renderer)},
      m_viewport{make_viewport(m_registry)}
{
  auto* view = m_registry.try_get<Viewport>(m_viewport);
  auto* level = m_registry.try_get<Tilemap>(m_world);
  view->set_level_size({level->width, level->height});

  humanoid::add_skeleton(m_registry, renderer);
}

void Game::handle_input(const Input& input)
{
  input::update(m_registry, m_player, input);
}

void Game::tick(const float delta)
{
  // TODO check if menu is blocking
  m_dispatcher.update();

  // Update game state
  humanoid::update_state(m_registry);

  // Animations
  humanoid::update_animation(m_registry);
  tile::update_animation(m_registry, m_world);  // FIXME m_world

  // Update stuff according to state
  update_movement(m_registry, delta);
  update_animation_state(m_registry);
  // TODO need to update viewport level size as well when level changes
  update_viewport(m_registry, m_viewport, m_player, delta);
}

void Game::render(Renderer& renderer, const float alpha)
{
  update_translation_viewport(m_registry, m_viewport, renderer);
  update_interpolation(m_registry, alpha);

  const auto& tilemap = m_registry.get<Tilemap>(m_world);  // FIXME m_world
  const auto bounds = calculate_render_bounds(
      m_registry, m_viewport, tilemap.rows, tilemap.cols);

  layer::render_ground(m_registry, m_world, renderer, bounds);

  // TODO render more stuff (think about render depth as well)
  render_movables(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
