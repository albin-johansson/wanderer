#include "quit_action.hpp"

#include "quit_event.hpp"

namespace wanderer {

void quit_action::execute(entt::dispatcher& dispatcher)
{
  dispatcher.enqueue<event::quit_event>();
}

}  // namespace wanderer
