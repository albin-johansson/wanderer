#pragma once
#include "menu.h"
#include "menu_state_machine.h"
#include "menu_button.h"

namespace wanderer::visuals {

class HomeMenu final : public IMenu {
 private:
  IMenuStateMachine* parent = nullptr;
  MenuButton startButton;

  float mx, my;

 public:
  explicit HomeMenu(IMenuStateMachine* parent);

  ~HomeMenu() override;

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  void HandleInput(const core::Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override {
    return true;
  }
};

}
