#pragma once
#include "entity_state.h"

namespace wanderer {

class Input;
class IWandererCore;

/**
 * The IPlayerState interface is a subinterface of IEntityState that specifies
 * objects that represent the state of a Player instance.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class IPlayerState : public IEntityState {
 protected:
  IPlayerState() = default;

 public:
  ~IPlayerState() override = default;

  /**
   * Reacts to the supplied input.
   *
   * @param input a reference to the input state.
   * @param core the associated core instance.
   * @since 0.1.0
   */
  virtual void handle_input(const Input& input, const IWandererCore& core) = 0;
};

}  // namespace wanderer