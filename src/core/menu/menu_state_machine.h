#pragma once
#include "menu.h"
#include "menu_id.h"

namespace wanderer::core {

class IMenuStateMachine : public IMenu {
 protected:
  IMenuStateMachine() = default;

 public:
  ~IMenuStateMachine() override = default;

  virtual void SetMenu(MenuID id) = 0;

  [[nodiscard]] virtual MenuID GetActiveMenuID() const noexcept = 0;
};

}
