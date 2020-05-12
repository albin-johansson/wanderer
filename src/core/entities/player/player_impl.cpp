#include "player_impl.h"

#include <texture.h>

#include "game_constants.h"
#include "input.h"
#include "player_state_machine_impl.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;

namespace albinjohansson::wanderer {

PlayerImpl::PlayerImpl(const Shared<Texture>& sheet) : AbstractEntity(sheet)
{
  playerStateMachine =
      std::make_unique<PlayerStateMachineImpl>(static_cast<IEntity*>(this));
  Init();
}

PlayerImpl::~PlayerImpl() = default;

void PlayerImpl::Init()
{
  set_speed(GameConstants::player_speed);
}

void PlayerImpl::handle_input(const Input& input, const IWandererCore& core)
{
  playerStateMachine->HandleInput(input, core);
}

void PlayerImpl::tick(IWandererCore& core, float delta)
{
  AbstractEntity::tick(core, delta);
  playerStateMachine->tick(core, delta);
}

void PlayerImpl::draw(Renderer& renderer,
                      const Viewport& viewport) const noexcept
{
  playerStateMachine->draw(renderer, viewport);
}

}  // namespace albinjohansson::wanderer
