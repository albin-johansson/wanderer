#pragma once
#include "types.h"

namespace wanderer {

void update_viewport(entt::registry& registry,
                     entt::entity viewport,
                     entt::entity player,
                     float delta);

}
