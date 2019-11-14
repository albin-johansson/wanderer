#pragma once
#include "game_object.h"
#include "drawable.h"
#include "image.h"
#include <memory>

namespace wanderer::core {

/**
 * The ITile interface specifies objects that represent tiles.
 *
 * @see IGameObject
 * @since 0.1.0
 */
class ITile : public IGameObject { // FIXME tiles should probably not implement IGameObject
 protected:
  ITile() = default;

 public:
  static constexpr float SIZE = 100;

  ~ITile() override = default;

  virtual void SetImage(visuals::Image_sptr image) noexcept = 0;

  [[nodiscard]] virtual visuals::Image_sptr GetImage() const noexcept = 0;

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
