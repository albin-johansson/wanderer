#include "abstract_tile.h"

namespace wanderer::core {

AbstractTile::AbstractTile(int row, int col, int id)
    : row(row), col(col), id(id) {
}

AbstractTile::~AbstractTile() = default;

void AbstractTile::Tick(float delta) {
  /* do nothing */
}

}