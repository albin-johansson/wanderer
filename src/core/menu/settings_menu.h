#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

class SettingsMenu final : public AbstractMenu {
 public:
  explicit SettingsMenu(IMenuStateMachine* parent);

  ~SettingsMenu() noexcept override;

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]] bool is_blocking() const noexcept override;
};

}  // namespace albinjohansson::wanderer
