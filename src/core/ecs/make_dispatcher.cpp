#include "make_dispatcher.hpp"

#include "event_connections.hpp"

namespace wanderer {

auto make_dispatcher() -> entt::dispatcher
{
  entt::dispatcher dispatcher;
  connect_events(dispatcher);
  return dispatcher;
}

}  // namespace wanderer
