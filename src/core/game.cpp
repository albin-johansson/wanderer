#include "game.h"

#include "game_constants.h"
#include "interpolation.h"
#include "make_player.h"
#include "make_viewport.h"
#include "movable.h"
#include "movement.h"
#include "player_input.h"
#include "rendering.h"
#include "update_translation_viewport.h"
#include "update_viewport.h"

using namespace centurion;

namespace wanderer {

void Game::init()
{
  m_player = make_player(m_registry);
  m_viewport = make_viewport(m_registry);
}

void Game::handle_input(const Input& input)
{
  update_input(m_registry, input);
}

void Game::tick(float delta)
{
  // TODO check if menu is blocking

  update_movement(m_registry, delta);

  // collision
  // attacks
  // interacts
  // enter/exit houses

  update_viewport(m_registry, m_viewport, m_player, delta);
}

void Game::render(Renderer& renderer, float alpha)
{
  update_translation_viewport(m_registry, m_viewport, renderer);
  interpolate(m_registry, alpha);

  // TODO render more stuff (think about render depth as well)
  render_player(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
