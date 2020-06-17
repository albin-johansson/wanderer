#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct BeginHumanoidMoveEvent final {
  entt::registry* registry{nullptr};
  entt::entity entity{entt::null};
  Direction direction{Direction::Down};

  BeginHumanoidMoveEvent(entt::registry* registry,
                         const entt::entity entity,
                         const Direction direction) noexcept
      : registry{registry}, entity{entity}, direction{direction}
  {}
};

}  // namespace wanderer
