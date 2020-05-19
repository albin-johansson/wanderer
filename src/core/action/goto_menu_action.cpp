#include "goto_menu_action.h"

namespace wanderer {

GotoMenuAction::GotoMenuAction(WeakPtr<IMenuStateMachine> menuStateMachine,
                               MenuID menu) noexcept
    : m_menuStateMachine{menuStateMachine}, m_menu{menu}
{}

void GotoMenuAction::execute() noexcept
{
  auto machine = m_menuStateMachine.lock();
  if (machine) {
    machine->set_menu(m_menu);
  }
}

}  // namespace wanderer
