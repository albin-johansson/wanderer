#include "abstract_entity_state.h"
#include "objects.h"

namespace wanderer::core {

AbstractEntityState::AbstractEntityState(IEntity* entity, IEntityStateMachine* parent) {
  this->entity = Objects::RequireNonNull(entity);
  this->parent = Objects::RequireNonNull(parent);
}

AbstractEntityState::~AbstractEntityState() = default;

}
