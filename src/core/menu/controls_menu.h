#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include <memory>

namespace wanderer::core {

class ControlsMenu final : public AbstractMenu {
 public:
  explicit ControlsMenu(IMenuStateMachine* parent);

  ~ControlsMenu() noexcept override;

  static IMenu_uptr Create(IMenuStateMachine* parent);

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override { return true; }
};

}
