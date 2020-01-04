#pragma once
#include "menu_id.h"

namespace centurion {

class Renderer;

}

namespace albinjohansson::wanderer {

class Input;
class Viewport;
class IMenu;

class IMenuStateMachine {
 protected:
  IMenuStateMachine() = default;

 public:
  virtual ~IMenuStateMachine() = default;

  virtual void HandleInput(const Input& input) = 0;

  virtual void Draw(centurion::Renderer& renderer, const Viewport& viewport) const = 0;

  /**
   * Sets the active menu.
   *
   * @param id the identifier associated with the desired menu.
   * @since 0.1.0
   */
  virtual void SetMenu(MenuID id) = 0;

  [[nodiscard]]
  virtual const IMenu& GetMenu() const = 0;
};

}
