#include "make_dispatcher.hpp"

#include "event_connections.hpp"

namespace wanderer {

auto MakeDispatcher() -> entt::dispatcher
{
  entt::dispatcher dispatcher;
  ConnectEvents(dispatcher);
  return dispatcher;
}

}  // namespace wanderer
