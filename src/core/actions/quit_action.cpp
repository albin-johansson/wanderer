#include "quit_action.hpp"

#include "quit_event.hpp"

namespace wanderer {

void quit_action::execute(entt::dispatcher& dispatcher)
{
  dispatcher.enqueue<comp::quit_event>();
}

}  // namespace wanderer
