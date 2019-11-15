#pragma once
#include "menu_state_machine.h"
#include "menu.h"
#include <map>

namespace wanderer::visuals {

class MenuStateMachineImpl final : public IMenuStateMachine {
 private:
  std::map<MenuID, IMenu_sptr> menus;
  IMenu_sptr activeMenu = nullptr;

 public:
  MenuStateMachineImpl();

  ~MenuStateMachineImpl() override;

  void Draw(visuals::Renderer& renderer, const core::Viewport& viewport) const noexcept override;

  void HandleInput(const core::Input& input) noexcept override;

  bool IsActiveMenuBlocking() const noexcept override;

  void SetMenu(MenuID id) noexcept override;

  MenuID GetActiveMenuID() const noexcept override;
};

}
