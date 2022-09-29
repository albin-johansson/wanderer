#pragma once

#include "wanderer/core/vocabulary.hpp"

namespace wanderer {

class Texture final {
 public:
  explicit Texture(const char* filename);

  ~Texture();

  void bind() const;

  [[nodiscard]] auto id() const -> uint { return mId; }

  [[nodiscard]] auto width() const -> int { return mWidth; }
  [[nodiscard]] auto height() const -> int { return mHeight; }

 private:
  uint mId {};
  int mWidth {};
  int mHeight {};
};

}  // namespace wanderer
