#pragma once

#include <renderer.h>
#include <texture.h>

#include <memory>
#include <string_view>

#include "wanderer_stdinc.h"

namespace wanderer {

class ImageLoader final : public entt::loader<ImageLoader, centurion::Texture> {
 public:
  [[nodiscard]] std::shared_ptr<centurion::Texture> load(
      centurion::Renderer& renderer,
      std::string_view path) const;
};

}  // namespace wanderer
