#pragma once
#include "menu.h"
#include "menu_id.h"
#include <memory>

namespace wanderer::core {

class IMenuStateMachine : public IMenu {
 protected:
  IMenuStateMachine() = default;

 public:
  ~IMenuStateMachine() override = default;

  virtual void SetMenu(MenuID id) = 0;

  [[nodiscard]] virtual MenuID GetActiveMenuID() const noexcept = 0;
};

using IMenuStateMachine_uptr = std::unique_ptr<IMenuStateMachine>;
using IMenuStateMachine_sptr = std::shared_ptr<IMenuStateMachine>;
using IMenuStateMachine_wptr = std::weak_ptr<IMenuStateMachine>;

}
