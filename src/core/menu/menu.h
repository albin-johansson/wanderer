#pragma once
#include "menu_drawable.h"

namespace wanderer {

class Input;

/**
 * The IMenu interface specifies objects that represent interactive menus in the
 * game.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IMenu : public IMenuDrawable {
 protected:
  IMenu() = default;

 public:
  ~IMenu() override = default;

  /**
   * Handles mouse and keyboard input.
   *
   * @param input a reference to the current input state.
   * @since 0.1.0
   */
  virtual void handle_input(const Input& input) noexcept = 0;

  /**
   * Indicates whether or not the menu is blocking. A blocking menu should
   * prevent the game from updating.
   *
   * @return true if the menu is a blocking menu; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool is_blocking() const noexcept = 0;
};

}  // namespace wanderer
