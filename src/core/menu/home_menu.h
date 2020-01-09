#pragma once
#include <memory>
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include "menu_button.h"
#include "wanderer_core.h"
#include "font_bundle.h"

namespace albinjohansson::wanderer {

/**
 * The HomeMenu class is an implementation of the IMenu interface that represents the main menu.
 *
 * @see IMenu
 * @since 0.1.0
 */
class HomeMenu final : public AbstractMenu {
 private:
  IWandererCore* core = nullptr;
  std::unique_ptr<FontBundle> fonts = nullptr;
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

  void draw(centurion::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]]
  inline bool is_blocking() const noexcept override {
    return true;
  }
};

}
