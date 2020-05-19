#include "quit_action.h"

namespace wanderer {

QuitAction::QuitAction(WeakPtr<IWandererCore> core) noexcept : m_core{core}
{}

void QuitAction::execute() noexcept
{
  auto core = m_core.lock();
  if (core) {
    core->quit();
  }
}

}  // namespace wanderer
