#pragma once
#include "tile_id.h"
#include "tile_map_bounds.h"
#include "renderer.h"
#include "viewport.h"
#include "drawable_tile.h"
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

class ITileMapLayer {
 protected:
  ITileMapLayer() = default;

 public:
  virtual ~ITileMapLayer() = default;

  virtual void Update(const TileMapBounds& bounds) = 0;

  virtual void Draw(Renderer& renderer,
                    const TileMapBounds& bounds,
                    const Viewport& viewport) const = 0;

  virtual void SetGroundLayer(bool isGroundLayer) noexcept = 0;

  [[nodiscard]] virtual TileID GetTileId(int row, int col) const = 0;

  [[nodiscard]] virtual const std::vector<TileID>& GetTiles() const noexcept = 0;

  [[nodiscard]] virtual std::vector<DrawableTile_sptr> CreateDrawableTiles() const = 0;

  [[nodiscard]] virtual int GetIndex(int row, int col) const noexcept = 0;

  [[nodiscard]] virtual bool IsGroundLayer() const noexcept = 0;

};

using ITileMapLayer_uptr = std::unique_ptr<ITileMapLayer>;
using ITileMapLayer_sptr = std::shared_ptr<ITileMapLayer>;
using ITileMapLayer_wptr = std::weak_ptr<ITileMapLayer>;

}
