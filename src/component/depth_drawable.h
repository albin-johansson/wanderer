#pragma once

#include <texture.h>

namespace wanderer {

struct DepthDrawable final {
  std::shared_ptr<centurion::Texture> texture;
  int srcX{0};
  int srcY{0};
  int depth{5};
};

}  // namespace wanderer
