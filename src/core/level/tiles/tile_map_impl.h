#pragma once
#include "tile_map.h"
#include "tile_map_bounds.h"
#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

class Rectangle;
class ImageGenerator;
class TileSet;
class ISortableDrawable;

/**
 * The TileMapImpl class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 private:
  std::weak_ptr<ITileMap> parent; // TODO doesn't need to be a weak pointer
  std::shared_ptr<TileSet> tileSet = nullptr;
  std::shared_ptr<IEntity> player = nullptr;

  std::vector<std::unique_ptr<ITileMapLayer>> groundLayers;
  std::vector<std::unique_ptr<ITileMapLayer>> objectLayers;

  std::vector<std::shared_ptr<IEntity>> entities;
  std::vector<std::shared_ptr<ISortableDrawable>> drawables;

  int nRows;
  int nCols;

  void Interpolate(float alpha);

  [[nodiscard]] TileMapBounds CalculateMapBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param tileSet a pointer to the associated tile set.
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMapImpl(std::shared_ptr<TileSet> tileSet,
              int nRows,
              int nCols,
              ImageGenerator& imageGenerator);

  ~TileMapImpl() override;

  void Tick(IWandererCore& core, const Viewport& viewport, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept override;

  void AddLayer(std::unique_ptr<ITileMapLayer> layer) override;

  void SetPlayer(std::shared_ptr<IEntity> player) override;

  void SetParent(std::weak_ptr<ITileMap> parent) override;

  [[nodiscard]] int GetRows() const noexcept override;

  [[nodiscard]] int GetCols() const noexcept override;

  [[nodiscard]] int GetWidth() const noexcept override;

  [[nodiscard]] int GetHeight() const noexcept override;

  [[nodiscard]] bool HasParent() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerSpawnPosition() const override;

  [[nodiscard]] std::weak_ptr<ITileMap> GetParent() const noexcept override;
};

}
