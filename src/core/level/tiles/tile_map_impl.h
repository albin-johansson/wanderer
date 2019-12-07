#pragma once
#include "tile_map.h"
#include "image_generator.h"
#include "tile.h"
#include "rectangle.h"
#include "image.h"
#include "tile_map_bounds.h"
#include "tile_set.h"
#include "wanderer_core.h"
#include "sortable_drawable.h"
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
  ITileMap_wptr parent;
  TileSet_sptr tileSet = nullptr;
  IEntity_sptr player = nullptr;

  std::vector<ITileMapLayer_uptr> groundLayers;
  std::vector<ITileMapLayer_uptr> objectLayers;
  std::vector<IEntity_sptr> entities;
  std::vector<ISortableDrawable_sptr> drawables;

  int nRows;
  int nCols;

  void Interpolate(float alpha);

  [[nodiscard]] TileMapBounds CalculateMapBounds(const Rectangle& bounds) const noexcept;

 public:
  /**
   * @param tileSet a shared pointer associated to the tile set.
   * @param nRows the number of rows in the tile map.
   * @param nCols the number of columns in the tile map.
   * @since 0.1.0
   */
  TileMapImpl(TileSet_sptr tileSet,
              int nRows,
              int nCols,
              ImageGenerator& imageGenerator);

  ~TileMapImpl() override;

  void Tick(IWandererCore& core, const Viewport& viewport, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport, float alpha) noexcept override;

  void AddObjectLayer(ITileMapLayer_uptr layer) override;

  void AddGroundLayer(ITileMapLayer_uptr layer) override;

  void SetPlayer(IEntity_sptr player) override;

  void SetParent(ITileMap_wptr parent) override;

  void AddDrawable(ISortableDrawable_sptr drawable) override;

  [[nodiscard]] int GetRows() const noexcept override { return nRows; }

  [[nodiscard]] int GetCols() const noexcept override { return nCols; }

  [[nodiscard]] int GetWidth() const noexcept override {
    return nCols * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] inline int GetHeight() const noexcept override {
    return nRows * static_cast<int>(Tile::SIZE);
  }

  [[nodiscard]] Vector2 GetPlayerSpawnPosition() const override;

  [[nodiscard]] bool HasParent() const noexcept override;

  [[nodiscard]] ITileMap_wptr GetParent() const noexcept override;

  [[nodiscard]] static bool CompareDrawables(const ISortableDrawable_sptr& first,
                                             const ISortableDrawable_sptr& second) noexcept;

};

}
