#pragma once

#include "wanderer/core/vocabulary.hpp"

namespace wanderer {

enum class ShaderType {
  Vertex,
  Fragment
};

class Shader final {
 public:
  Shader(ShaderType type, const char* filename);

  ~Shader();

  [[nodiscard]] auto id() const -> uint { return mId; }

 private:
  uint mId;
};

}  // namespace wanderer
