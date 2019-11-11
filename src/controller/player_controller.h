#pragma once
#include "key_state_manager.h"
#include "wanderer_controller.h"

namespace wanderer::controller {

/**
 * The PlayerController class is responsible for controlling the player entity.
 *
 * @since 0.1.0
 */
class PlayerController final {
 private:
  IWandererController* controller = nullptr;

  /**
   * Checks for pressed keys.
   *
   * @param keyStateManager the key state manager that holds the relevant key state.
   * @since 0.1.0
   */
  void CheckPressed(const KeyStateManager& keyStateManager);

  /**
   * Checks for released keys.
   *
   * @param keyStateManager the key state manager that holds the relevant key state.
   * @since 0.1.0
   */
  void CheckReleased(const KeyStateManager& keyStateManager);

 public:
  /**
   * @param controller a pointer to the parent controller instance. Note! The created player
   * controller will note free the parent controller upon destruction.
   * @since 0.1.0
   */
  explicit PlayerController(IWandererController* controller);

  ~PlayerController();

  /**
   * Updates the state of the player controller.
   *
   * @param keyStateManager a reference to the key state manager that provides the current key
   * state.
   * @since 0.1.0
   */
  void Update(const KeyStateManager& keyStateManager);
};

}
