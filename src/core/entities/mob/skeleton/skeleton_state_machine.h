#pragma once
#include "abstract_entity_state_machine.h"

namespace wanderer::core {

class SkeletonStateMachine final : public AbstractEntityStateMachine<IEntityState> {
 public:
  explicit SkeletonStateMachine(IEntity* entity);

  ~SkeletonStateMachine() override;
};

}
