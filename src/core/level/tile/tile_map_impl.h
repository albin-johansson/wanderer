#pragma once
#include <rect.h>
#include <renderer.h>

#include <memory>
#include <vector>

#include "entity_manager.h"
#include "spawnpoint.h"
#include "tile_map.h"
#include "tile_map_bounds.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class TileSet;
class ISortableDrawable;
class IGameObject;

/**
 * The TileMapImpl class represents a map of tiles, used to build the game
 * world. Use the TileMapBuilder class to create instances of this class.
 *
 * @see TileMapBuilder
 * @since 0.1.0
 */
class TileMapImpl final : public ITileMap {
 public:
  ~TileMapImpl() override;

  void tick(IWandererCore& core,
            const Viewport& viewport,
            float delta) override;

  void draw(ctn::Renderer& renderer,
            const Viewport& viewport,
            float alpha) noexcept override;

  void add_layer(UniquePtr<ITileMapLayer>&& layer) override;

  void set_player(const SharedPtr<IEntity>& player) override;

  [[nodiscard]] bool is_blocked(const IMovableObject* self,
                                float delta) const override;

  [[nodiscard]] int get_rows() const noexcept override;

  [[nodiscard]] int get_cols() const noexcept override;

  [[nodiscard]] int get_width() const noexcept override;

  [[nodiscard]] int get_height() const noexcept override;

  [[nodiscard]] Vector2 get_player_spawn_position() const override;

 private:
  friend class TileMapBuilder;

  SharedPtr<TileSet> m_tileSet = nullptr;
  SharedPtr<IEntity> m_player = nullptr;
  std::vector<UniquePtr<ITileMapLayer>> m_groundLayers;
  std::vector<UniquePtr<ITileMapLayer>> m_objectLayers;
  std::vector<IGameObject*> m_activeObjects;

  EntityManager m_entityManager;

  std::vector<Spawnpoint> m_spawnpoints;

  int m_nRows = 0;
  int m_nCols = 0;
  Vector2 m_playerSpawnPos;

  void render_tiles_at(int row, int col, ctn::Renderer& renderer);

  /**
   * Interpolates all movable game objects.
   *
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  void interpolate(float alpha);

  /**
   * Calculates the tile map bounds.
   *
   * @param bounds the bounds of the viewport.
   * @return the tile map bounds.
   * @since 0.1.0
   */
  [[nodiscard]] TileMapBounds calc_map_bounds(
      const ctn::FRect& bounds) const noexcept;

  /**
   * @param tileSet the associated tile set.
   * @since 0.1.0
   */
  explicit TileMapImpl(const SharedPtr<TileSet>& tileSet);
};

}  // namespace wanderer
