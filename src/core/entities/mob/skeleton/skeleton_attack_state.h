#pragma once
#include "entity_state.h"
#include "entity_attack_delegate.h"
#include "entity_state_machine.h"

namespace albinjohansson::wanderer {

class SkeletonAttackState final : public IEntityState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  explicit SkeletonAttackState(IEntityStateMachine* parent);

  ~SkeletonAttackState() override;

  void Tick(const IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const IWandererCore& core) override;

  void Exit(const IWandererCore& core) override;

};

}
