#pragma once
#include "game_object.h"
#include "drawable.h"
#include <memory>

namespace wanderer::core {

// TODO see the solution Notch used for one of his ludum dare games, where only the ID is stored
//  and there are only one actual instance of the Tile class that describes the different types.

/**
 * The ITile interface specifies objects that represent tiles.
 *
 * @see IGameObject
 * @since 0.1.0
 */
class ITile : public IGameObject {
 protected:
  ITile() = default;

 public:
  static constexpr int SIZE = 200;

  ~ITile() override = default;

  /**
   * Returns the row index of the tile.
   *
   * @return the row index of the tile.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetRow() const noexcept = 0;

  /**
   * Returns the column index of the tile.
   *
   * @return the column index of the tile.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetCol() const noexcept = 0;

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
