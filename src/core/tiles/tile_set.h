#pragma once
#include <map>
#include "tile.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"

namespace albinjohansson::wanderer {

class TileSet final {
 private:
  std::map<int, ITile_uptr> tiles;

 public:
  TileSet();

  ~TileSet();

//  void Draw(Renderer& renderer, const Viewport& viewport, int row, int col, int id);

  bool IsBlocked(int id) const;

  void SetImage(int id, Image_sptr img);

  Image_sptr GetImage(int id) const;
};

}
