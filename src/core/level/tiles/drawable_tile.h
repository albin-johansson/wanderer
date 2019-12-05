#pragma once
#include "tile_id.h"
#include "sortable_drawable.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include <memory>

namespace albinjohansson::wanderer {

class DrawableTile : public ISortableDrawable {
 private:
  const float x = 0;
  const float y = 0;
  TileSet_wptr tileSet;

 public:
  const TileID id = 0;

  DrawableTile(float x, float y, TileID id, TileSet_wptr tileSet);

  ~DrawableTile() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;
};

using DrawableTile_uptr = std::unique_ptr<DrawableTile>;
using DrawableTile_sptr = std::shared_ptr<DrawableTile>;
using DrawableTile_wptr = std::weak_ptr<DrawableTile>;

}