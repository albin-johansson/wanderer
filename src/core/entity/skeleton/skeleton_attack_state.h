#pragma once
#include "entity_attack_delegate.h"
#include "entity_state.h"

namespace albinjohansson::wanderer {

class IEntityStateMachine;

class SkeletonAttackState final : public IEntityState {
 private:
  EntityAttackDelegate attackDelegate;

 public:
  explicit SkeletonAttackState(IEntityStateMachine* parent);

  ~SkeletonAttackState() override;

  void tick(const IWandererCore& core, float delta) override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;
};

}  // namespace albinjohansson::wanderer
