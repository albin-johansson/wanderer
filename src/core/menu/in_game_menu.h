#pragma once
#include "menu_state_machine.h"
#include "menu.h"

namespace wanderer::core {

class InGameMenu final : public IMenu {
 private:
  IMenuStateMachine* parent = nullptr;

 public:
  explicit InGameMenu(IMenuStateMachine* parent);

  ~InGameMenu() override;

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  void HandleInput(const core::Input& input) noexcept override;

  [[nodiscard]] inline bool IsBlocking() const noexcept override {
    return false;
  }
};

}
