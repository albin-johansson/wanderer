#include "tile_image_set.h"
#include <bad_state_exception.h>
#include <string>

namespace albinjohansson::wanderer {

TileImageSet::TileImageSet() { sheets.reserve(5); }

TileImageSet::~TileImageSet() = default;

void TileImageSet::Add(SpriteSheet_uptr sheet) {
  sheets.push_back(std::move(sheet));
}

const Rectangle& TileImageSet::GetSource(int tileId) const {
  for (const auto& sheet : sheets) {
    if (sheet->Contains(tileId)) {
      return sheet->GetSource(tileId);
    }
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(tileId));
}

Image_sptr TileImageSet::GetImage(int tileId) const {
  for (const auto& sheet : sheets) {
    if (sheet->Contains(tileId)) {
      return sheet->GetImage();
    }
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(tileId));
}

}
