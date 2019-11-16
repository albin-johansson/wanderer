#pragma once
#include "menu.h"
#include "menu_state_machine.h"

namespace wanderer::core {

class AbstractMenu : public IMenu {
 protected:
  IMenuStateMachine* parent = nullptr;

  explicit AbstractMenu(IMenuStateMachine* parent);

 public:
  ~AbstractMenu() noexcept override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

};

}
