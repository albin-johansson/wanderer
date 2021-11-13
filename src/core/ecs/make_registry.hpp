#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer {

[[nodiscard]] auto MakeRegistry() -> entt::registry;

}  // namespace wanderer
