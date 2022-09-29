#pragma once

#include <centurion/window.hpp>

#include "wanderer/core/vocabulary.hpp"
#include "wanderer/gfx/shader_program.hpp"
#include "wanderer/gfx/texture.hpp"
#include "wanderer/type/maybe.hpp"

namespace wanderer {

/// Represents the simplified main rendering API.
class Renderer final {
 public:
  explicit Renderer(cen::window& window);

  ~Renderer();

  /// Prepares for rendering a new frame.
  /// This will update the viewport, enable the default shaders, and clear the screen.
  void begin_frame();

  /// Finishes a rendering pass by swapping the window frame buffers.
  void end_frame();

  [[nodiscard]] auto vbo() const -> uint { return mVBO; }
  [[nodiscard]] auto vao() const -> uint { return mVAO; }
  [[nodiscard]] auto ebo() const -> uint { return mEBO; }

 private:
  cen::window& mWindow;
  ShaderProgram mDefault;

  uint mVBO {};  ///< Vertex Buffer Object
  uint mVAO {};  ///< Vertex Array Object
  uint mEBO {};
};

}  // namespace wanderer
