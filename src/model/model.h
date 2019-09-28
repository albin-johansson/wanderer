#pragma once
#include "player.h"
#include "direction.h"
#include <memory>
#include <vector>

namespace wanderer::model {

/**
 * The IModel class is an interface that specifies the facade for the model component of the
 * application.
 *
 * @since 0.1.0
 */
class IModel {
 protected:
  IModel() = default;

 public:
  virtual ~IModel() = default;

  /**
   * Updates the model state.
   *
   * @param delta the delta time that will be used.
   * @since 0.1.0
   */
  virtual void Update(double delta) = 0;

  /**
   * Sets the player to move in the specified direction.
   *
   * @param direction the direction in which the player should move in.
   * @since 0.1.0
   */
  virtual void MovePlayer(Direction direction) = 0;

  /**
   * Sets the player to stop moving in the specified direction.
   *
   * @param direction the direction in which the player should stop moving in.
   * @since 0.1.0
   */
  virtual void StopPlayer(Direction direction) = 0;

  virtual Player_sptr GetPlayer() = 0;

};

using IModel_uptr = std::unique_ptr<IModel>;
using IModel_sptr = std::shared_ptr<IModel>;
using IModel_wptr = std::weak_ptr<IModel>;

} // namespace wanderer::model