#include "sprite_sheet.h"
#include "objects.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

SpriteSheet::SpriteSheet(Image_sptr otherSheet, Range range, int otherSize)
    : range(range),
      size(static_cast<float>(otherSize)) {
  this->sheet = Objects::RequireNonNull(std::move(otherSheet));
  nCols = static_cast<int>(sheet->GetWidth() / size);
  nRows = static_cast<int>(sheet->GetHeight() / size);
  nSprites = nRows * nCols;

  TileID id = range.min;
  for (int i = 0; i < nSprites; i++, id++) {
    auto row = i / nCols;
    auto col = i % nCols;
    Rectangle rect(col * size, row * size, size, size);

    sourceRectangles.insert(std::pair<TileID, Rectangle>(id, rect));
  }
}

SpriteSheet::~SpriteSheet() = default;

const Rectangle& SpriteSheet::GetSource(TileID spriteId) const {
  return sourceRectangles.at(spriteId);
}

}
