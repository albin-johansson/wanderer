#pragma once
#include "tile_id.h"
#include "drawable_tile.h"
#include <vector>
#include <memory>

namespace albinjohansson::wanderer {

class TileRenderGroup final : public ISortableDrawable {
 private:
  std::vector<DrawableTile_sptr> tiles;
  const float pivotX = 0;
  const float pivotY = 0;

 public:
  TileRenderGroup(float pivotX, float pivotY, std::vector<DrawableTile_sptr> tiles);

  TileRenderGroup(float pivotX, float pivotY, std::vector<DrawableTile_sptr>&& tiles);

  ~TileRenderGroup() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;

};

using TileRenderGroup_uptr = std::unique_ptr<TileRenderGroup>;
using TileRenderGroup_sptr = std::shared_ptr<TileRenderGroup>;
using TileRenderGroup_wptr = std::weak_ptr<TileRenderGroup>;

}
