#pragma once
#include "entity_state.h"
#include "entity.h"
#include "animation.h"

namespace wanderer::core {

/**
 * The EntityDyingDelegate class is an implementation of IEntityState that is meant to be used for
 * delegating idle entity dying calls.
 *
 * @see IEntityState
 * @since 0.1.0
 */
class EntityDyingDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;
  visuals::Animation animation;

 public:
  /**
   * @param entity a pointer to the associate entity instance.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityDyingDelegate(IEntity* entity);

  ~EntityDyingDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter() override;

  void Exit() override;

  void Tick(float delta) override;
};

}
