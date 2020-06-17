#pragma once

#include <renderer.h>

#include "types.h"

namespace wanderer::system::humanoid {

entt::entity add_player(entt::registry& registry,
                        centurion::Renderer& renderer);

entt::entity add_skeleton(entt::registry& registry,
                          centurion::Renderer& renderer);

}  // namespace wanderer::system::humanoid
