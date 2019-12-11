#pragma once
#include "tile_id.h"
#include "map_position.h"
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

class TileObject;
class TileMapBounds;
class ISortableDrawable;
class Renderer;
class Viewport;

class ITileMapLayer {
 protected:
  ITileMapLayer() = default;

 public:
  virtual ~ITileMapLayer() = default;

  virtual void Update(const TileMapBounds& bounds) = 0;

  virtual void DrawTile(Renderer& renderer,
                        const MapPosition& position,
                        const Viewport& viewport) const = 0;

  virtual void SetGroundLayer(bool isGroundLayer) noexcept = 0;

  virtual void AddObjects(const TileMapBounds& bounds,
                          std::vector<std::shared_ptr<ISortableDrawable>>& drawables) = 0;

  [[nodiscard]] virtual TileID GetTileId(int row, int col) const = 0;

  [[nodiscard]] virtual const std::vector<TileID>& GetTiles() const noexcept = 0;

  [[nodiscard]] virtual MapPosition GetPosition(int index) const noexcept = 0;

  [[nodiscard]] virtual int GetIndex(int row, int col) const noexcept = 0;

  [[nodiscard]] virtual bool IsGroundLayer() const noexcept = 0;
};

}
