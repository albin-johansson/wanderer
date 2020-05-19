#pragma once
#include "action/action.h"
#include "menu_id.h"
#include "menu_state_machine.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class GotoMenuAction final : public IAction {
 public:
  GotoMenuAction(WeakPtr<IMenuStateMachine> menuStateMachine,
                 MenuID menu) noexcept;

  ~GotoMenuAction() noexcept override = default;

  void execute() noexcept override;

 private:
  WeakPtr<IMenuStateMachine> m_menuStateMachine;
  MenuID m_menu;
};

}  // namespace wanderer
