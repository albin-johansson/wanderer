#include "goto_menu_action.h"

namespace albinjohansson::wanderer {

GotoMenuAction::GotoMenuAction(weak<IMenuStateMachine> menuStateMachine,
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

}  // namespace albinjohansson::wanderer
