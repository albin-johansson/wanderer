#pragma once
#include <texture.h>

#include "vector_2.h"

namespace wanderer {

struct Drawable final {
  std::shared_ptr<centurion::Texture> texture;
  int srcY{0};
};

}  // namespace wanderer
