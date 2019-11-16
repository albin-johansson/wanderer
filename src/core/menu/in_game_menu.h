#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include <memory>

namespace wanderer::core {

/**
 * The InGameMenu class is an implementation of the IMenu interface that represents the in-game
 * menu.
 *
 * @see IMenu
 * @since 0.1.0
 */
class InGameMenu final : public AbstractMenu {
 public:
  /**
   * @param parent a pointer to the parent state machine, will not be freed.
   * @throws NullPointerException if the supplied parent pointer is null.
   * @since 0.1.0
   */
  explicit InGameMenu(IMenuStateMachine* parent);

  ~InGameMenu() override;

  static IMenu_uptr Create(IMenuStateMachine* parent);

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  void HandleInput(const core::Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override {
    return false;
  }
};

}
