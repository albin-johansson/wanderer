#pragma once
#include "sortable_drawable.h"
#include "tile_id.h"
#include "tile_set.h"
#include "vector_2.h"
#include <memory>

namespace albinjohansson::wanderer {

class DrawableTile : public ISortableDrawable { // FIXME remove
 private:
  TileSet_wptr tileSet;
  Vector2 position;

 public:
  const TileID id = 0;

  DrawableTile(float x, float y, TileID id, TileSet_wptr tileSet);

  ~DrawableTile() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  [[nodiscard]] float GetCenterY() const noexcept override;
};

using DrawableTile_uptr = std::unique_ptr<DrawableTile>;
using DrawableTile_sptr = std::shared_ptr<DrawableTile>;
using DrawableTile_wptr = std::weak_ptr<DrawableTile>;

}