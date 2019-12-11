#pragma once
#include "tile_map_layer.h"
#include "tile_id.h"
#include "vector_2.h"
#include <vector>
#include <unordered_map>

namespace albinjohansson::wanderer {

class TileSet;

class TileMapLayerImpl final : public ITileMapLayer {
 private:
  const int nRows;
  const int nCols;
  std::shared_ptr<TileSet> tileSet = nullptr;
  std::vector<TileID> tiles;
  std::unordered_map<int, std::shared_ptr<TileObject>> tileObjects;
  bool isGroundLayer = false;

  void InitTileObjects();

  [[nodiscard]] Vector2 CreatePosition(int index) const;

 public:
  TileMapLayerImpl(std::shared_ptr<TileSet> tileSet,
                   int nRows,
                   int nCols,
                   std::vector<TileID> tiles);

  ~TileMapLayerImpl() noexcept override;

  void Update(const TileMapBounds& bounds) override;

  void DrawTile(Renderer& renderer,
                const MapPosition& position,
                const Viewport& viewport) const override;

  void SetGroundLayer(bool isGroundLayer) noexcept override;

  void AddObjects(const TileMapBounds& bounds,
                  std::vector<std::shared_ptr<ISortableDrawable>>& drawables) override;

  [[nodiscard]] TileID GetTileId(int row, int col) const override;

  [[nodiscard]] bool IsGroundLayer() const noexcept override;

  [[nodiscard]] MapPosition GetPosition(int index) const noexcept override;

  [[nodiscard]] int GetIndex(int row, int col) const noexcept override;

  [[nodiscard]] const std::vector<TileID>& GetTiles() const noexcept override;

};

}