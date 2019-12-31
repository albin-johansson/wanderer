#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

class SettingsMenu final : public AbstractMenu {
 public:
  explicit SettingsMenu(IMenuStateMachine* parent);

  ~SettingsMenu() noexcept override;

  void Draw(Renderer& renderer, const Viewport& viewport, FontBundle& fonts) const override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]]
  bool IsBlocking() const noexcept override;
};

}
