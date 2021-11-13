#pragma once

#include <entt/entt.hpp>  // dispatcher

namespace wanderer {

[[nodiscard]] auto MakeDispatcher() -> entt::dispatcher;

}  // namespace wanderer
