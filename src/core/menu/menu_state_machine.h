#pragma once
#include "menu_id.h"
#include "input.h"
#include "drawable.h"

namespace wanderer::visuals {

class IMenuStateMachine : public core::IDrawable {
 protected:
  IMenuStateMachine() = default;

 public:
  ~IMenuStateMachine() override = default;

  virtual void HandleInput(const core::Input& input) noexcept = 0;

  virtual void SetMenu(MenuID id) = 0;

  [[nodiscard]] virtual bool IsActiveMenuBlocking() const noexcept = 0;

  [[nodiscard]] virtual MenuID GetActiveMenuID() const noexcept = 0;
};

}
