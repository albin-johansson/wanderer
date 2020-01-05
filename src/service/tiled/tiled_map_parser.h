#pragma once
#include <memory>
#include <string>

namespace albinjohansson::wanderer {

class ITileMap;
class ImageGenerator;

class TiledMapParser final {
 public:
  TiledMapParser() = delete;

  ~TiledMapParser() = default;

  [[nodiscard]]
  static std::unique_ptr<ITileMap> load(ImageGenerator& imageGenerator,
                                        const std::string& file);

};

}
