#pragma once
#include "tile_map_layer.h"
#include "renderer.h"
#include "viewport.h"
#include "entity.h"
#include "vector_2.h"
#include <memory>

namespace albinjohansson::wanderer {

class ITileMap;

using ITileMap_uptr = std::unique_ptr<ITileMap>;
using ITileMap_sptr = std::shared_ptr<ITileMap>;
using ITileMap_wptr = std::weak_ptr<ITileMap>;

class ISortableDrawable;
using ISortableDrawable_sptr = std::shared_ptr<ISortableDrawable>;

class ITileMap {
 protected:
  ITileMap() = default;

 public:
  virtual ~ITileMap() = default;

  virtual void Tick(IWandererCore& core, const Viewport& viewport, float delta) = 0;

  virtual void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept = 0;

  virtual void AddObjectLayer(ITileMapLayer_uptr layer) = 0;

  virtual void AddGroundLayer(ITileMapLayer_uptr layer) = 0;

  virtual void AddDrawable(ISortableDrawable_sptr drawable) = 0;

  virtual void SetPlayer(IEntity_sptr player) = 0;

  virtual void SetParent(ITileMap_wptr parent) = 0;

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

  [[nodiscard]] virtual bool HasParent() const noexcept = 0;

  [[nodiscard]] virtual ITileMap_wptr GetParent() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerSpawnPosition() const = 0;

};

}
