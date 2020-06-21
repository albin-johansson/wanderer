#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct BeginAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon component entity tag
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
