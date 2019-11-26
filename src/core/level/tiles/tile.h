#pragma once
#include "game_object.h"
#include "drawable.h"
#include "image.h"
#include <memory>

namespace albinjohansson::wanderer {

struct TilePos {
  int row = 0;
  int col = 0;
};

class IEntity;

/**
 * The ITile interface specifies objects that represent tiles.
 *
 * @see IGameObject
 * @since 0.1.0
 */
class ITile {
 protected:
  ITile() = default;

 public:
  static constexpr float SIZE = 64;

  virtual ~ITile() = default;

  virtual void Draw(TilePos pos, Renderer& renderer, const Viewport& viewport) const = 0;

  virtual void Tick(ILevel& level, float delta) = 0;

  virtual void Hurt(int x, int y, const IEntity& source, int dmg) = 0;

  virtual void BumpInto(int x, int y, const IEntity& source) = 0;

  [[nodiscard]] virtual Image& GetImage() const = 0;

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetId() const noexcept = 0;

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool IsBlocked() const noexcept = 0;
};

using ITile_uptr = std::unique_ptr<ITile>;
using ITile_sptr = std::shared_ptr<ITile>;
using ITile_wptr = std::weak_ptr<ITile>;

}
