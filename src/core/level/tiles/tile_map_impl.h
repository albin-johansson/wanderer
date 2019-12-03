#pragma once
#include "tile_map.h"
#include "image_generator.h"
#include "tile.h"
#include "rectangle.h"
#include "image.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "wanderer_core.h"
#include <vector>

namespace albinjohansson::wanderer {

// TODO Tiled map loading
//  - Layers
//  - Animated tiles

/**
 * The TileMapImpl class represents a map of tiles, used to build the game world.
 *
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 private:
//  ITileMap_wptr parent; bool HasParentLevel(); void ExitLevel();

  std::unique_ptr<TileSet> tileSet = nullptr;
  std::vector<ITileMapLayer_uptr> layers; // TODO separate different layers such as ground, etc?

  // std::vector<TileMapLayer_uptr> groundLayers;
  // std::vector<TileMapLayer_uptr> objectLayers

  std::vector<IEntity_sptr> entities;
  IEntity_sptr player = nullptr;

  int nRows;
  int nCols;

  void Interpolate(float alpha);

  [[nodiscard]] TileMapBounds CalculateMapBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param tileSet a unique pointer associated to the tile set.
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMapImpl(std::unique_ptr<TileSet> tileSet,
              int nRows,
              int nCols,
              ImageGenerator& imageGenerator);

  ~TileMapImpl() override;

  void Tick(IWandererCore& core, const Viewport& viewport, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept override;

  void AddLayer(ITileMapLayer_uptr layer) override;

  void SetPlayer(IEntity_sptr player) override;

  [[nodiscard]] inline int GetRows() const noexcept override { return nRows; }

  [[nodiscard]] int GetCols() const noexcept override { return nCols; }

  [[nodiscard]] int GetWidth() const noexcept override {
    return nCols * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] inline int GetHeight() const noexcept override {
    return nRows * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] Vector2 GetPlayerSpawnPosition() const override;

  [[nodiscard]] bool HasParent() const noexcept override;

  [[nodiscard]] ITileMap* GetParent() const noexcept override;

  [[nodiscard]] static bool CompareGameObjects(const IGameObject_sptr& first,
                                               const IGameObject_sptr& second) noexcept;

};

}
