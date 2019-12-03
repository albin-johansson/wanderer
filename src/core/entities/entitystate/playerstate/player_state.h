#pragma once
#include "entity_state.h"
#include "input.h"
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The IPlayerState interface is a subinterface of IEntityState that specifies objects that
 * represent the state of a Player instance.
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
   * Reacts to the supplied input
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input, const IWandererCore& core) = 0;
};

using IPlayerState_uptr = std::unique_ptr<IPlayerState>;
using IPlayerState_sptr = std::shared_ptr<IPlayerState>;
using IPlayerState_wptr = std::weak_ptr<IPlayerState>;

}