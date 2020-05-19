#pragma once
#include "entity_state.h"

namespace wanderer {

class IEntityStateMachine;

class EntityMoveDelegate final : public IEntityState {
 private:
  IEntityStateMachine* parent = nullptr;

 public:
  explicit EntityMoveDelegate(IEntityStateMachine* parent);

  ~EntityMoveDelegate() override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

  void tick(const IWandererCore& core, float delta) override;

  void UpdateAnimation();

  void UpdatePosition(float delta);

  [[nodiscard]] IEntityStateMachine& get_parent() noexcept;
};

}  // namespace wanderer
