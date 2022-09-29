#pragma once

#include "wanderer/core/vocabulary.hpp"

namespace wanderer {

class ShaderProgram final {
 public:
  /// Loads a shader program with the specified vertex and fragment shaders.
  ShaderProgram(const char* vertex_path, const char* fragment_path);

  ~ShaderProgram();

  /// Enables the associated shaders for subsequent rendering calls.
  void use() const;

  void set_uniform(const char* name, bool value);
  void set_uniform(const char* name, int value);
  void set_uniform(const char* name, float value);

  [[nodiscard]] auto id() const -> uint { return mId; }

 private:
  uint mId;
};

}  // namespace wanderer
