#include "player_attack_state.h"

namespace wanderer::core {

PlayerAttackState::PlayerAttackState(IEntity* entity, IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(entity, parent)) {}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::HandleInput(const Input& input, const IGame& game) {
}

}
