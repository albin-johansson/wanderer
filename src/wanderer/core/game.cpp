#include "game.hpp"

#include <GL/glew.h>
#include <centurion/event.hpp>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

#include "wanderer/core/error.hpp"

namespace wanderer {

Game::Game()
    : mWindow {"Wanderer",
               {800, 600},
               cen::window::hidden | cen::window::allow_high_dpi | cen::window::opengl}
    , mGL {mWindow}
{
  if (mGL.make_current(mWindow) == cen::failure) {
    throw Error {"Failed to use window with OpenGL context!"};
  }

  SDL_GL_SetSwapInterval(1);  // Use VSync

  if (glewInit() != GLEW_OK) {
    throw Error {"Call to glewInit failed!"};
  }

  spdlog::debug("[OpenGL] Version: {}", (const char*) glGetString(GL_VERSION));
  spdlog::debug("[OpenGL] Renderer: {}", (const char*) glGetString(GL_RENDERER));
  spdlog::debug("[OpenGL] Swap interval: {}", SDL_GL_GetSwapInterval());

  mRenderer.emplace(mWindow);
  mPanda.emplace("assets/panda.png");

  register_events();
}

void Game::run()
{
  mWindow.show();
  start();
  mWindow.hide();
}

void Game::process_events()
{
  mContext.mouse.update();
  mContext.keyboard.refresh();

  cen::event_handler event;
  while (event.poll()) {
    if (event.is(cen::event_type::quit)) {
      stop();
    }
  }
}

void Game::update(const float32 dt)
{
  mContext.dispatcher.update();

  if (mCurrentState) {
    mCurrentState->update(mContext, dt);
  }
}

void Game::render()
{
  mRenderer->begin_frame();


  mRenderer->end_frame();
}

void Game::register_events()
{
  mContext.dispatcher.sink<QuitEvent>().connect<&Game::on_quit>(this);
  mContext.dispatcher.sink<ChangeStateEvent>().connect<&Game::on_change_state>(this);
}

void Game::on_quit()
{
  stop();
}

void Game::on_change_state(const wanderer::ChangeStateEvent& event)
{
  spdlog::debug("[Game] Changing game state to '{}'...",
                magic_enum::enum_name(event.state));
}

}  // namespace wanderer