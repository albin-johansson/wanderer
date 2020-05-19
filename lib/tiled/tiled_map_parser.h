#pragma once
#include <texture_loader.h>

#include <memory>
#include <string>

namespace wanderer {

class ITileMap;

class TiledMapParser final {
 public:
  TiledMapParser() = delete;

  ~TiledMapParser() = default;

  [[nodiscard]] static std::unique_ptr<ITileMap> load(
      centurion::TextureLoader& textureLoader, const std::string& file);
};

}  // namespace wanderer
