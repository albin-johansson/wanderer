#pragma once
#include <renderer.h>

#include "menu_id.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class Input;
class Viewport;
class IMenu;

class IMenuStateMachine {
 public:
  virtual ~IMenuStateMachine() = default;

  virtual void handle_input(const Input& input) = 0;

  virtual void draw(ctn::Renderer& renderer,
                    const Viewport& viewport) const = 0;

  virtual void add_menu(MenuID id, Unique<IMenu> menu) = 0;

  /**
   * Sets the active menu.
   *
   * @param id the identifier associated with the desired menu.
   * @since 0.1.0
   */
  virtual void set_menu(MenuID id) = 0;

  [[nodiscard]] virtual const IMenu& get_menu() const = 0;
};

}  // namespace albinjohansson::wanderer
