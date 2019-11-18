#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_dying_delegate.h"

namespace wanderer::core {

class PlayerDyingState final : public IPlayerState {
 private:
  EntityDyingDelegate dyingDelegate;

 public:
  PlayerDyingState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerDyingState() override;

  void HandleInput(const Input& input) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) override {
    dyingDelegate.Draw(renderer, viewport);
  }

  inline void Tick(float delta) override { dyingDelegate.Tick(delta); }

  inline void Enter() override { dyingDelegate.Enter(); }

  inline void Exit() override { dyingDelegate.Exit(); }
};

}
