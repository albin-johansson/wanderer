#pragma once

#include <texture.h>

#include <entt.hpp>

namespace wanderer {

struct DepthDrawable final {
  entt::handle<centurion::Texture> texture;
  int srcX{0};
  int srcY{0};
  int depth{5};
};

}  // namespace wanderer
