#include "grass_tile.h"

namespace albinjohansson::wanderer {

GrassTile::GrassTile(Image_sptr image, int id) : AbstractTile(std::move(image), id) {}

GrassTile::~GrassTile() = default;

void GrassTile::Hurt(int x, int y, const IEntity& source, int dmg) {}

void GrassTile::BumpInto(int x, int y, const IEntity& source) {}

}