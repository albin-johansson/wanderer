#include "tile_image_set.h"
#include <bad_state_exception.h>
#include <string>

namespace albinjohansson::wanderer {

TileImageSet::TileImageSet() { sheets.reserve(5); }

TileImageSet::~TileImageSet() = default;

void TileImageSet::Add(SpriteSheet_uptr sheet) {
  sheets.push_back(std::move(sheet));
}

Rectangle TileImageSet::GetSource(int tileId) const {
  // TODO see if the index stuff can be simplified

  int nBefore = 1;
  for (const auto& sheet : sheets) {
    if (sheet->Contains(tileId)) {
      int index = tileId - nBefore;
      return sheet->GetSource(index);
    }

    nBefore += (sheet->GetMaxID() - 1);
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(tileId));
}

Image& TileImageSet::GetImage(int tileId) const {
  for (const auto& sheet : sheets) {
    if (sheet->Contains(tileId)) {
      return sheet->GetImage();
    }
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(tileId));
}

}
