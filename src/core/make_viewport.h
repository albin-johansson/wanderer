#pragma once

#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer {

[[nodiscard]] ViewportEntity make_viewport(entt::registry& registry);

}  // namespace wanderer
