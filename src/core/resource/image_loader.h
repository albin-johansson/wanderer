#pragma once

#include <renderer.h>
#include <texture.h>

#include <memory>
#include <string_view>

#include "wanderer_stdinc.h"

namespace wanderer {

class ImageLoader final : public entt::loader<ImageLoader, ctn::Texture> {
 public:
  [[nodiscard]] auto load(ctn::Renderer& renderer, std::string_view path) const
      -> std::shared_ptr<ctn::Texture>;
};

}  // namespace wanderer
