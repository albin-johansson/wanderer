#pragma once
#include "abstract_entity_state_machine.h"

namespace wanderer {

class SkeletonStateMachine final : public AbstractEntityStateMachine<> {
 public:
  explicit SkeletonStateMachine(IEntity* entity);

  ~SkeletonStateMachine() override;
};

}  // namespace wanderer
