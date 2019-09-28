#pragma once
#include "controller.h"
#include "ctn_key_listener.h"
#include "ctn_mouse_listener.h"
#include "objects.h"

namespace wanderer::controller {

/**
 * The InputHandler class is responsible for handling the mouse and key input.
 *
 * @since 0.1.0
 */
class InputHandler final : public centurion::input::IKeyListener,
                           public centurion::input::IMouseListener {
 private:
  IController* controller = nullptr;

  void CheckMovementInput(const centurion::input::KeyState& state);

 public:
  /**
   * @param controller a raw pointer to the parent controller instance, the created input handler
   * will NOT delete the pointer upon finalization.
   * @throws invalid_argument if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit InputHandler(IController* controller) noexcept {
    this->controller = model::Objects::RequireNonNull(controller);
  }

  void KeyStateUpdated(const centurion::input::KeyState& state) override;

  void MouseStateUpdated(const centurion::input::MouseState& mouse) override;

};

} // namespace wanderer::controller