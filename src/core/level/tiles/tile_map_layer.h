#pragma once
#include "tile_id.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "renderer.h"
#include "viewport.h"
#include <memory>

namespace albinjohansson::wanderer {

class ITileMapLayer {
 protected:
  ITileMapLayer() = default;

 public:
  virtual ~ITileMapLayer() = default;

  virtual void Update(const TileMapBounds& bounds, TileSet& tileSet) = 0;

  virtual void Draw(Renderer& renderer,
                    const TileMapBounds& bounds,
                    const Viewport& viewport,
                    const TileSet& tileSet) const = 0;

  [[nodiscard]] virtual TileID GetTileId(int row, int col) const = 0;

  [[nodiscard]] virtual const std::vector<TileID>& GetTiles() const noexcept = 0;

  [[nodiscard]] virtual int GetIndex(int row, int col) const noexcept = 0;

};

using ITileMapLayer_uptr = std::unique_ptr<ITileMapLayer>;
using ITileMapLayer_sptr = std::shared_ptr<ITileMapLayer>;
using ITileMapLayer_wptr = std::weak_ptr<ITileMapLayer>;

}
