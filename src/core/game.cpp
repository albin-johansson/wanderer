#include "game.h"

#include <colors.h>

using namespace centurion;

namespace wanderer {

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
  renderer.set_color(color::cyan);
  renderer.clear();
}

}  // namespace wanderer
