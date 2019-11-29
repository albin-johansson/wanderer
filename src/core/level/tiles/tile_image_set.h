#pragma once
#include <vector>
#include <memory>
#include "sprite_sheet.h"

namespace albinjohansson::wanderer {

class TileImageSet final {
 private:
  std::vector<SpriteSheet_uptr> sheets;

 public:
  TileImageSet();

  ~TileImageSet();

  void Add(SpriteSheet_uptr sheet);

  [[nodiscard]] const Rectangle& GetSource(int tileId) const;

  [[nodiscard]] Image_sptr GetImage(int tileId) const;

};

}
