#include "abstract_tile.h"

namespace albinjohansson::wanderer {

AbstractTile::AbstractTile(int row, int col, int id)
    : row(row), col(col), id(id) {
}

AbstractTile::~AbstractTile() = default;

void AbstractTile::Tick(const ILevel& level, float delta) {
/* do nothing */
}

void AbstractTile::SetImage(Image_sptr image) noexcept {
  this->image = image;
}

}