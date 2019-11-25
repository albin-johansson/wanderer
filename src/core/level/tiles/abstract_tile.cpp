#include "abstract_tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

AbstractTile::AbstractTile(Image_sptr img, int id) : id(id) {
  this->image = Objects::RequireNonNull(std::move(img));
}

AbstractTile::~AbstractTile() = default;

void AbstractTile::Tick(ILevel& level, float delta) {
/* do nothing */
}

void AbstractTile::Draw(TilePos pos, Renderer& renderer, const Viewport& viewport) const {
  auto x = viewport.GetTranslatedX(static_cast<float>(pos.col) * ITile::SIZE);
  auto y = viewport.GetTranslatedY(static_cast<float>(pos.row) * ITile::SIZE);
  renderer.RenderTexture(*image, x, y, ITile::SIZE, ITile::SIZE);
}

}