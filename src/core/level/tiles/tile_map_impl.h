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
class IGameObject;

/**
 * The TileMapImpl class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 private:
  std::shared_ptr<TileSet> tileSet = nullptr; // FIXME not needed as field
  std::shared_ptr<IEntity> player = nullptr;

  std::vector<std::unique_ptr<ITileMapLayer>> groundLayers;
  std::vector<std::unique_ptr<ITileMapLayer>> objectLayers;

  std::vector<std::shared_ptr<IEntity>> entities;
  std::vector<IGameObject*> activeObjects;

  const int nRows;
  const int nCols;

  /**
   * Interpolates all movable game objects.
   *
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void Interpolate(float alpha);

  /**
   * Calculates the tile map bounds.
   *
   * @param bounds the bounds of the viewport.
   * @return the tile map bounds.
   * @since 0.1.0
   */
  [[nodiscard]] TileMapBounds CalculateMapBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param tileSet a pointer to the associated tile set.
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @param imageGenerator a reference to the image generator that will be used.
   * @since 0.1.0
   */
  TileMapImpl(const std::shared_ptr<TileSet>& tileSet,
              int nRows,
              int nCols,
              ImageGenerator& imageGenerator);

  ~TileMapImpl() override;

  void Tick(IWandererCore& core, const Viewport& viewport, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept override;

  void AddLayer(std::unique_ptr<ITileMapLayer>&& layer) override;

  void SetPlayer(const std::shared_ptr<IEntity>& player) override;

  [[nodiscard]] bool IsBlocked(const IMovableObject* self, float delta) const override;

  [[nodiscard]] int GetRows() const noexcept override;

  [[nodiscard]] int GetCols() const noexcept override;

  [[nodiscard]] int GetWidth() const noexcept override;

  [[nodiscard]] int GetHeight() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerSpawnPosition() const override;
};

}
