#pragma once
#include "player_state.h"
#include "entity.h"
#include "entity_state_machine.h"
#include "entity_attack_delegate.h"

namespace wanderer::core {

class PlayerAttackState final : public IPlayerState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  PlayerAttackState(IEntity* entity, IEntityStateMachine* parent);

  ~PlayerAttackState() override;

  void HandleInput(const Input& input) override;

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) override {
    attackDelegate.Draw(renderer, viewport);
  }

  inline void Tick(float delta) override { attackDelegate.Tick(delta); }

  inline void Enter() override { attackDelegate.Enter(); }

  inline void Exit() override { attackDelegate.Exit(); }

};

}
