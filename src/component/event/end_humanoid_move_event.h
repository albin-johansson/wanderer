#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct EndHumanoidMoveEvent final {
  entt::registry* registry{nullptr};
  entt::entity entity{entt::null};

  EndHumanoidMoveEvent(entt::registry* registry,
                       const entt::entity entity) noexcept
      : registry{registry}, entity{entity}
  {}
};

}  // namespace wanderer
