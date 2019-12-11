#pragma once
#include "vector_2.h"
#include <memory>

namespace albinjohansson::wanderer {

class IWandererCore;
class TileObject;
class ITileMapLayer;
class IEntity;
class Viewport;
class Renderer;

class ITileMap {
 protected:
  ITileMap() = default;

 public:
  virtual ~ITileMap() = default;

  virtual void Tick(IWandererCore& core, const Viewport& viewport, float delta) = 0;

  virtual void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept = 0;

  virtual void AddLayer(std::unique_ptr<ITileMapLayer> layer) = 0;

  virtual void SetPlayer(std::shared_ptr<IEntity> player) = 0;

  virtual void SetParent(std::weak_ptr<ITileMap> parent) = 0;

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

  [[nodiscard]] virtual std::weak_ptr<ITileMap> GetParent() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerSpawnPosition() const = 0;

};

}
