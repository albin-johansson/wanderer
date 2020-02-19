#pragma once
#include <texture_loader.h>

#include <memory>
#include <string>

namespace albinjohansson::wanderer {

class ITileMap;

class TiledMapParser final {
 public:
  TiledMapParser() = delete;

  ~TiledMapParser() = default;

  [[nodiscard]] static std::unique_ptr<ITileMap> load(
      centurion::video::TextureLoader& imageGenerator, const std::string& file);
};

}  // namespace albinjohansson::wanderer
