#pragma once
#include "tile_map_layer.h"
#include "renderer.h"
#include "viewport.h"
#include <memory>

namespace albinjohansson::wanderer {

class ITileMap {
 protected:
  ITileMap() = default;

 public:
  virtual ~ITileMap() = default;

  virtual void Tick(const Viewport& viewport) = 0;

  virtual void Draw(Renderer& renderer, const Viewport& viewport) const noexcept = 0;

  virtual void AddLayer(ITileMapLayer_uptr layer) = 0;

  /**
   * Returns the number of rows in the tile map.
   *
   * @return the number of rows in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetRows() const noexcept = 0;

  /**
   * Returns the number of columns in the tile map.
   *
   * @return the number of columns in the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetCols() const noexcept = 0;

  /**
   * Returns the width of the tile map.
   *
   * @return the width of the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetWidth() const noexcept = 0;

  /**
   * Returns the height of the tile map.
   *
   * @return the height of the tile map.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetHeight() const noexcept = 0;

};

using ITileMap_uptr = std::unique_ptr<ITileMap>;
using ITileMap_sptr = std::shared_ptr<ITileMap>;
using ITileMap_wptr = std::weak_ptr<ITileMap>;

}
