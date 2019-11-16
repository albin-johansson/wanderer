#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include "menu_button.h"
#include <memory>

namespace wanderer::core {

/**
 * The HomeMenu class is an implementation of the IMenu interface that represents the main menu.
 *
 * @see IMenu
 * @since 0.1.0
 */
class HomeMenu final : public AbstractMenu {
 private:
  MenuButton startButton;
  MenuButton settingsButton;
  MenuButton controlsButton;
  MenuButton quitButton;

 public:
  /**
  * @param parent a pointer to the parent state machine, will not be freed.
  * @throws NullPointerException if the supplied parent pointer is null.
  * @since 0.1.0
  */
  explicit HomeMenu(IMenuStateMachine* parent);

  ~HomeMenu() noexcept override;

  static IMenu_uptr Create(IMenuStateMachine* parent);

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) override;

  void HandleInput(const core::Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override {
    return true;
  }
};

}
