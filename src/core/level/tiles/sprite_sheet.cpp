#include "sprite_sheet.h"
#include "objects.h"

namespace albinjohansson::wanderer {

SpriteSheet::SpriteSheet(Image_sptr sheet, Range range, int size)
    : range(range),
      size(static_cast<float>(size)) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));

  nCols = this->sheet->GetWidth() / size;
  nRows = this->sheet->GetHeight() / size;

  nSprites = nRows * nCols;
}

SpriteSheet::~SpriteSheet() = default;

Rectangle SpriteSheet::GetSource(int index) const {
  auto col = (index % nCols);
  auto row = (index / nCols);
  return Rectangle(col * size, row * size, size, size);
}

}
