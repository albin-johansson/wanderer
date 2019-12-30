#pragma once
#include <memory>
#include <string>

namespace albinjohansson::wanderer {

class ITileMap;
class ImageGenerator;

class TiledMapParser final {
 public:
  TiledMapParser();

  ~TiledMapParser();

  [[nodiscard]] std::unique_ptr<ITileMap> Load(ImageGenerator& imageGenerator,
                                               const std::string& file) const;

};

}
