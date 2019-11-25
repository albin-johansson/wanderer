#pragma once
#include "abstract_tile.h"

namespace albinjohansson::wanderer {

/**
 * The GrassTile class is a subclass of AbstractTile that represents a tile of grass.
 *
 * @see AbstractTile
 * @since 0.1.0
 */
class GrassTile final : public AbstractTile {
 public:
  GrassTile(Image_sptr image, int id);

  ~GrassTile() override;

  void Hurt(int x, int y, const IEntity& source, int dmg) override;

  void BumpInto(int x, int y, const IEntity& source) override;

  [[nodiscard]] inline bool IsBlocked() const noexcept override { return false; }
};

}
