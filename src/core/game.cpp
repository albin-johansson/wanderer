#include "game.h"

#include "animation_system.h"
#include "game_constants.h"
#include "ground_layer_rendering_system.h"
#include "humanoid_animation_system.h"
#include "humanoid_state_system.h"
#include "input_system.h"
#include "interpolation_system.h"
#include "make_map.h"
#include "make_player.h"
#include "make_viewport.h"
#include "movement_system.h"
#include "render_movables_system.h"
#include "tile_animation_system.h"
#include "tilemap.h"
#include "translation_viewport_system.h"
#include "viewport.h"
#include "viewport_system.h"

using namespace centurion;

namespace wanderer {

Game::Game(Renderer& renderer)
    : m_player{make_player(m_registry, renderer)},
      m_world{make_map(m_registry, "world_demo.json", renderer)},
      m_viewport{make_viewport(m_registry)}
{
  auto* view = m_registry.try_get<Viewport>(m_viewport);
  auto* level = m_registry.try_get<Tilemap>(m_world);
  view->set_level_size({level->width, level->height});
}

void Game::handle_input(const Input& input)
{
  update_input(m_registry, m_player, input);
}

void Game::tick(const float delta)
{
  // TODO check if menu is blocking

  // Update game state
  humanoids_update_state(m_registry);

  // Animations
  humanoids_update_animation(m_registry);
  tiles_update_animation(m_registry, m_world);  // FIXME should be curr. level

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

  render_ground_layers(m_registry, m_world, m_viewport, renderer);

  // TODO render more stuff (think about render depth as well)
  render_movables(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
