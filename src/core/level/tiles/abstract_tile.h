#pragma once
#include "tile.h"
#include "level.h"
#include "image.h"

namespace albinjohansson::wanderer {

/**
 * The AbstractTile class is an abstract class that partially implements the ITile interface.
 *
 * @see ITile
 * @since 0.1.0
 */
class AbstractTile : public ITile {
 private:
  Image_sptr image = nullptr;
  const int id;

 protected:
  AbstractTile(Image_sptr image, int id);

 public:
  ~AbstractTile() override;

  void Tick(ILevel& level, float delta) override;

  void Draw(TilePos pos, Renderer& renderer, const Viewport& viewport) const override;

  [[nodiscard]] int GetId() const noexcept final { return id; }

  [[nodiscard]] Image& GetImage() const override { return *image; }

};

}
