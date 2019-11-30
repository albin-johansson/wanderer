#include "tile_image_set.h"
#include <bad_state_exception.h>
#include <string>

namespace albinjohansson::wanderer {

TileImageSet::TileImageSet() { sheets.reserve(5); }

TileImageSet::~TileImageSet() = default;

void TileImageSet::Add(SpriteSheet_uptr sheet) {
  sheets.push_back(std::move(sheet));
}

const Rectangle& TileImageSet::GetSource(TileID id) const {
  for (const auto& sheet : sheets) {
    if (sheet->Contains(id)) {
      return sheet->GetSource(id);
    }
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(id));
}

Image_sptr TileImageSet::GetImage(TileID id) const {
  for (const auto& sheet : sheets) {
    if (sheet->Contains(id)) {
      return sheet->GetImage();
    }
  }

  throw BadStateException("Invalid tile ID: " + std::to_string(id));
}

}
