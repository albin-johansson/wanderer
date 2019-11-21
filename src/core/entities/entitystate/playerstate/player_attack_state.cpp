#include "player_attack_state.h"

namespace wanderer::core {

PlayerAttackState::PlayerAttackState(IEntityStateMachine* parent)
    : attackDelegate(EntityAttackDelegate(parent)) {}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::HandleInput(const Input& input, const IGame& game) {
}

}
