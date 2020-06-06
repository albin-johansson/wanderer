#include "game.h"

#include <humanoid_animation_system.h>

#include "make_player.h"
#include "make_viewport.h"
#include "render_entities.h"
#include "update_animation.h"
#include "update_input.h"
#include "update_interpolation.h"
#include "update_movement.h"
#include "update_translation_viewport.h"
#include "update_viewport.h"

using namespace centurion;

namespace wanderer {

Game::Game(Renderer& renderer)
    : m_player{make_player(m_registry, renderer)},
      m_viewport{make_viewport(m_registry)}
{}

void Game::handle_input(const Input& input)
{
  update_input(m_registry, m_player, input);
}

void Game::tick(float delta)
{
  // TODO check if menu is blocking

  update_movement(m_registry, delta);

  //  const auto es = m_registry.view<EntityMo>()
  humanoid_update_move(m_registry, m_player);  // FIXME hardcoded

  update_animation(m_registry);

  // update movement
  // update collision
  // update attack
  // update interact (NPCs/enter/exit houses)
  // update animation

  // TODO need to update viewport level size as well when level changes

  update_viewport(m_registry, m_viewport, m_player, delta);
}

void Game::render(Renderer& renderer, float alpha)
{
  update_translation_viewport(m_registry, m_viewport, renderer);
  update_interpolation(m_registry, alpha);

  // TODO render more stuff (think about render depth as well)
  render_entities(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
