#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include "menu_button.h"
#include "wanderer_core.h"
#include "font_bundle.h"
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
  IWandererCore* core = nullptr;
  visuals::FontBundle_uptr fonts = nullptr;
  mutable MenuButton startButton;
  mutable MenuButton settingsButton;
  mutable MenuButton controlsButton;
  mutable MenuButton quitButton;

 public:
  /**
  * @param parent a pointer to the parent state machine, will not be freed.
  * @param core the associated wanderer core instance.
  * @throws NullPointerException if any pointers are null.
  * @since 0.1.0
  */
  HomeMenu(IMenuStateMachine* parent, IWandererCore* core);

  ~HomeMenu() noexcept override;

  static IMenu_uptr Create(IMenuStateMachine* parent, IWandererCore* core);

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const override;

  void HandleInput(const core::Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override {
    return true;
  }
};

}
