#include "player_dying_state.h"

namespace albinjohansson::wanderer {

PlayerDyingState::PlayerDyingState(IEntity* entity)
    : dyingDelegate(entity) {}

PlayerDyingState::~PlayerDyingState() = default;

void PlayerDyingState::HandleInput(const Input& input, const IGame& game) {}

}
