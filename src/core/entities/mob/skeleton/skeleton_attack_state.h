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

  void Tick(const ILevel& level, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const ILevel& level) override;

  void Exit(const ILevel& level) override;

};

}
