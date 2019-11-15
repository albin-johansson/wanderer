#pragma once
#include "input.h"
#include "drawable.h"
#include <memory>

namespace wanderer::visuals {

/**
 * The IMenu interface specifies objects that represent interactive menus in the game.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IMenu : public IDrawable {
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
  virtual void HandleInput(const Input& input) noexcept = 0;

  /**
   * Indicates whether or not the menu is blocking. A blocking menu should prevent the game from
   * updating.
   *
   * @return true if the menu is a blocking menu; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool IsBlocking() const noexcept = 0;
};

using IMenu_uptr = std::unique_ptr<IMenu>;
using IMenu_sptr = std::shared_ptr<IMenu>;
using IMenu_wptr = std::weak_ptr<IMenu>;

}
