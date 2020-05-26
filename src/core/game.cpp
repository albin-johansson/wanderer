#include "game.h"

#include "interpolation.h"
#include "make_player.h"
#include "movement.h"
#include "player_input.h"
#include "rendering.h"

using namespace centurion;

namespace wanderer {

void Game::init()
{
  m_player = make_player(m_registry);
}

void Game::handle_input(const Input& input)
{
  update_input(m_registry, input);
}

void Game::tick(float delta)
{
  update_movement(m_registry, delta);
  // collision
  // attacks
  // interacts
  // enter/exit houses
}

void Game::render(Renderer& renderer, float alpha)
{
  // TODO renderer.set_translation_viewport(...)
  interpolate(m_registry, alpha);
  render_player(m_registry, renderer);
}

}  // namespace wanderer
