#pragma once
#include <memory>
#include <vector>
#include <rectangle.h>
#include "tile_map.h"
#include "tile_map_bounds.h"
#include "entity_manager.h"
#include "spawnpoint.h"
#include "renderer.h"

namespace albinjohansson::wanderer {

class TileSet;
class ISortableDrawable;
class IGameObject;

/**
 * The TileMapImpl class represents a map of tiles, used to build the game world. Use the
 * TileMapBuilder class to create instances of this class.
 *
 * @see TileMapBuilder
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 private:
  friend class TileMapBuilder;

  int nRows = 0;
  int nCols = 0;
  Vector2 playerSpawnPos;

  std::shared_ptr<TileSet> tileSet = nullptr;
  std::shared_ptr<IEntity> player = nullptr;

  std::vector<std::unique_ptr<ITileMapLayer>> groundLayers;
  std::vector<std::unique_ptr<ITileMapLayer>> objectLayers;
  std::vector<IGameObject*> activeObjects;

  EntityManager entityManager;

  std::vector<Spawnpoint> spawnpoints;

  void RenderTilesAt(int row, int col, centurion::Renderer& renderer);

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
  [[nodiscard]]
  TileMapBounds CalculateMapBounds(const centurion::FRect& bounds) const noexcept;

  /**
   * @param tileSet the associated tile set.
   * @since 0.1.0
   */
  explicit TileMapImpl(const std::shared_ptr<TileSet>& tileSet);

 public:
  ~TileMapImpl() override;

  void tick(IWandererCore& core, const Viewport& viewport, float delta) override;

  void draw(centurion::Renderer& renderer, const Viewport& viewport, float alpha) noexcept override;

  void add_layer(std::unique_ptr<ITileMapLayer>&& layer) override;

  void set_player(const std::shared_ptr<IEntity>& player) override;

  [[nodiscard]]
  bool is_blocked(const IMovableObject* self, float delta) const override;

  [[nodiscard]]
  int get_rows() const noexcept override;

  [[nodiscard]]
  int get_cols() const noexcept override;

  [[nodiscard]]
  int get_width() const noexcept override;

  [[nodiscard]]
  int get_height() const noexcept override;

  [[nodiscard]]
  Vector2 get_player_spawn_position() const override;
};

}
