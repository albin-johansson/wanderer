#include "player_impl.h"
#include "player_state_machine_impl.h"
#include "image.h"
#include "input.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

PlayerImpl::PlayerImpl(const std::shared_ptr<Image>& sheet) : AbstractEntity(sheet) {
  playerStateMachine = std::make_unique<PlayerStateMachineImpl>(static_cast<IEntity*>(this));
  Init();
}

PlayerImpl::~PlayerImpl() = default;

void PlayerImpl::Init() {
  set_speed(playerSpeed);
}

void PlayerImpl::HandleInput(const Input& input, const IWandererCore& core) {
  playerStateMachine->HandleInput(input, core);
}

void PlayerImpl::tick(IWandererCore& core, float delta) {
  AbstractEntity::tick(core, delta);
  playerStateMachine->Tick(core, delta);
}

void PlayerImpl::Draw(const Renderer& renderer, const Viewport& viewport) const noexcept {
  playerStateMachine->Draw(renderer, viewport);
}

}
