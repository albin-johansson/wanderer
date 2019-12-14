#pragma once
#include "entity.h"

namespace albinjohansson::wanderer {

class Input;

/**
 * The IPlayer interface specifies the player in the game.
 *
 * @see IEntity
 * @since 0.1.0
 */
class IPlayer : public virtual IEntity {
 protected:
  IPlayer() = default;

 public:
  ~IPlayer() override = default;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state object.
   * @param core a reference to the associated core instance.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input, const IWandererCore& core) = 0;
};

}