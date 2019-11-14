#pragma once
#include <map>
#include "tile.h"
#include "image.h"
#include "renderer.h"
#include "viewport.h"

namespace wanderer::core {

class TileSet final {
 private:
  std::map<int, ITile_uptr> tiles;

 public:
  TileSet();

  ~TileSet();

//  void Draw(visuals::Renderer& renderer, const Viewport& viewport, int row, int col, int id);

  bool IsBlocked(int id) const;

  void SetImage(int id, visuals::Image_sptr img);

  visuals::Image_sptr GetImage(int id) const;
};

}
