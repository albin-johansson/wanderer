#pragma once
#include <map>
#include "tile.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"
#include "image_generator.h"

namespace albinjohansson::wanderer {

class TileSet final {
 private:
  std::map<int, ITile_uptr> tiles;

  [[nodiscard]] static std::map<int, Image_sptr> LoadTileImages(ImageGenerator& imageGenerator);

 public:
  explicit TileSet(ImageGenerator& imageGenerator);

  ~TileSet();

  [[nodiscard]] const ITile& GetTile(int id) const;
};

}
