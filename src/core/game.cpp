#include "game.h"

#include <colors.h>

#include "make_player.h"
#include "render.h"

using namespace centurion;

namespace wanderer {

void Game::init()
{
  make_player(m_registry);
}

void Game::handle_input(const Input& input)
{
  // TODO player input system
}

void Game::tick(float delta)
{
  // TODO call appropriate systems

  // movement
  // collision
  // attacks
  // interacts
  // enter/exit houses
}

void Game::render(Renderer& renderer, float alpha)
{
  render_player(m_registry, renderer, alpha);
}

}  // namespace wanderer
