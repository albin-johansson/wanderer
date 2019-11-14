#include "tile_set.h"
#include "grass_tile.h"

using namespace wanderer::visuals;

namespace wanderer::core {

TileSet::TileSet() {
  tiles.insert(std::pair<int, ITile_uptr>(0, std::make_unique<GrassTile>(0, 0, 0)));
}

TileSet::~TileSet() = default;

void TileSet::SetImage(int id, visuals::Image_sptr img) {
  tiles.at(id)->SetImage(img);
}

bool TileSet::IsBlocked(int id) const {
  return tiles.at(id)->IsBlocked();
}

Image_sptr TileSet::GetImage(int id) const {
  return tiles.at(id)->GetImage();
}

}
