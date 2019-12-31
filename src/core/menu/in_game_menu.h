#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

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

  void Draw(Renderer& renderer, const Viewport& viewport, const FontBundle& fonts) const override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]]
  bool IsBlocking() const noexcept override;
};

}
