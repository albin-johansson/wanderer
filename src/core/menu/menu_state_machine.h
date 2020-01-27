#pragma once
#include "menu_id.h"
#include "renderer.h"

namespace albinjohansson::wanderer {

class Input;
class Viewport;
class IMenu;

class IMenuStateMachine {
 public:
  virtual ~IMenuStateMachine() = default;

  virtual void handle_input(const Input& input) = 0;

  virtual void draw(centurion::Renderer& renderer, const Viewport& viewport) const = 0;

  /**
   * Sets the active menu.
   *
   * @param id the identifier associated with the desired menu.
   * @since 0.1.0
   */
  virtual void set_menu(MenuID id) = 0;

  [[nodiscard]]
  virtual const IMenu& get_menu() const = 0;
};

}
