#include "game.h"

#include <colors.h>

#include "game_constants.h"
#include "humanoid_animation_system.h"
#include "humanoid_state_system.h"
#include "input_system.h"
#include "interpolation_system.h"
#include "make_player.h"
#include "make_viewport.h"
#include "movement_system.h"
#include "render_movables_system.h"
#include "translation_viewport_system.h"
#include "update_animation.h"
#include "viewport_system.h"

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

void Game::tick(const float delta)
{
  // TODO check if menu is blocking

  humanoids_update_state(m_registry);
  humanoids_update_animation(m_registry);
  update_movables(m_registry, delta);
  update_animation_state(m_registry);
  // TODO need to update viewport level size as well when level changes
  update_viewport(m_registry, m_viewport, m_player, delta);
}

void Game::render(Renderer& renderer, const float alpha)
{
  update_translation_viewport(m_registry, m_viewport, renderer);
  update_interpolation(m_registry, alpha);

  renderer.set_color(color::red);

  const auto ts = g_tileSize;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 20; ++j) {
      const auto x = static_cast<float>(j) * ts;
      const auto y = static_cast<float>(i) * ts;
      renderer.draw_rect_tf({{x, y}, {ts, ts}});
    }
  }

  // TODO render more stuff (think about render depth as well)
  render_movables(m_registry, renderer);

  // TODO render HUD

  // TODO render menus
}

}  // namespace wanderer
