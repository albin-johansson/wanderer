#pragma once
#include <memory>
#include <string>
#include "image_generator.h"

namespace albinjohansson::wanderer {

class ITileMap;

class TiledMapParser final {
 public:
  TiledMapParser() = delete;

  ~TiledMapParser() = default;

  [[nodiscard]]
  static std::unique_ptr<ITileMap> load(centurion::ImageGenerator& imageGenerator,
                                        const std::string& file);

};

}
