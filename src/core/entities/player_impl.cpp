#include "player_impl.h"
#include "player_state_machine_impl.h"
#include "image.h"
#include "input.h"
#include "renderer.h"
#include "viewport.h"
#include "wanderer_core.h"

namespace albinjohansson::wanderer {

PlayerImpl::PlayerImpl(std::shared_ptr<Image> sheet) : AbstractEntity(std::move(sheet)) {
  playerStateMachine = std::make_unique<PlayerStateMachineImpl>(static_cast<IEntity*>(this));
}

void PlayerImpl::HandleInput(const Input& input, const IWandererCore& core) {
  playerStateMachine->HandleInput(input, core);
}

void PlayerImpl::Tick(IWandererCore& core, float delta) {
  AbstractEntity::Tick(core, delta);
  playerStateMachine->Tick(core, delta);
}

void PlayerImpl::Draw(Renderer& renderer, const Viewport& viewport) const noexcept {
  playerStateMachine->Draw(renderer, viewport);
}

}
