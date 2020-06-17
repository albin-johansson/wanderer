#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct BeginAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};
  entt::entity weapon{entt::null};
  Direction direction{Direction::Down};

  BeginAttackEvent(entt::registry* registry,
                   const entt::entity sourceEntity,
                   const entt::entity weapon,
                   const Direction direction)
      : registry{registry},
        sourceEntity{sourceEntity},
        weapon{weapon},
        direction{direction}
  {}
};

}  // namespace wanderer
