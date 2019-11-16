#pragma once
#include "entity_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "animation.h"
#include "entity_draw_delegate.h"

namespace wanderer::core {

class AbstractEntityState : public IEntityState {
 protected:
  IEntity* entity = nullptr;
  IEntityStateMachine* parent = nullptr;
  EntityDrawDelegate drawDelegate;
  visuals::Animation animation;

  AbstractEntityState(IEntity* entity, IEntityStateMachine* parent);

 public:
  ~AbstractEntityState() override;

};

}
