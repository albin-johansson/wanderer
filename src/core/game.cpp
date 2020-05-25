#include "game.h"

#include <colors.h>

using namespace centurion;

namespace wanderer {

void Game::handle_input(const Input& input)
{}

void Game::tick(float delta)
{}

void Game::render(Renderer& renderer, float alpha)
{
  renderer.set_color(color::cyan);
  renderer.clear();
}

}  // namespace wanderer
