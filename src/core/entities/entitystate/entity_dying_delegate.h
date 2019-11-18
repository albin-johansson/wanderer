#pragma once
#include "entity_state.h"
#include "entity.h"
#include "animation.h"

namespace wanderer::core {

class EntityDyingDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  visuals::Animation animation;

 public:
  explicit EntityDyingDelegate(IEntity* entity);

  ~EntityDyingDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter() override;

  void Exit() override;

  void Tick(float delta) override;
};

}
