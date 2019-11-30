#pragma once
#include <vector>
#include <memory>
#include "sprite_sheet.h"
#include "tile.h"

namespace albinjohansson::wanderer {

class TileImageSet final {
 private:
  std::vector<SpriteSheet_uptr> sheets;

 public:
  TileImageSet();

  ~TileImageSet();

  void Add(SpriteSheet_uptr sheet);

  [[nodiscard]] const Rectangle& GetSource(TileID id) const;

  [[nodiscard]] Image_sptr GetImage(TileID id) const;

};

}
