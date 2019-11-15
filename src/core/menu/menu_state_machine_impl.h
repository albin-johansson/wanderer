#pragma once
#include "menu_state_machine.h"
#include <map>

namespace wanderer::core {

class MenuStateMachineImpl final : public IMenuStateMachine {
 private:
  std::map<MenuID, IMenu_sptr> menus;
  IMenu_sptr activeMenu = nullptr;

 public:
  MenuStateMachineImpl();

  ~MenuStateMachineImpl() override;

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  void HandleInput(const Input& input) noexcept override;

  bool IsBlocking() const noexcept override;

  void SetMenu(MenuID id) noexcept override;

  MenuID GetActiveMenuID() const noexcept override;
};

}
