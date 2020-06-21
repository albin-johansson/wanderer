#pragma once

#include "direction.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct EndAttackEvent final {
  entt::registry* registry{nullptr};
  entt::entity sourceEntity{entt::null};  // TODO tag type
  entt::entity weapon{entt::null};        // TODO weapon tag type
  Direction direction{Direction::Down};

  EndAttackEvent(entt::registry* registry,
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
