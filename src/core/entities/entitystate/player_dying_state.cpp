#include "player_dying_state.h"

namespace wanderer::core {

PlayerDyingState::PlayerDyingState(IEntity* entity, IEntityStateMachine* parent)
    : dyingDelegate(entity) {}

PlayerDyingState::~PlayerDyingState() = default;

void PlayerDyingState::HandleInput(const Input& input) {}

}
