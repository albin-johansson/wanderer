#include "renderer.hpp"

#include <GL/glew.h>
#include <centurion/opengl.hpp>

namespace wanderer {

Renderer::Renderer(cen::window& window)
    : mWindow {window}
    , mDefault {"shaders/vert.glsl", "shaders/frag.glsl"}
{
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);
}

Renderer::~Renderer()
{
  glDeleteBuffers(1, &mEBO);
  glDeleteBuffers(1, &mVBO);
  glDeleteVertexArrays(1, &mVAO);
}

void Renderer::begin_frame()
{
  const auto window_size = mWindow.size();

#ifdef __APPLE__
  glViewport(0, 0, window_size.width * 2, window_size.height * 2);
#else
  glViewport(0, 0, window_size.width, window_size.height);
#endif  // __APPLE__

  mDefault.use();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::end_frame()
{
  cen::gl::swap(mWindow);
}

}  // namespace wanderer
