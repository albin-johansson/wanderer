#pragma once
#include "entity_state.h"
#include "entity.h"

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

 public:
  /**
   * @param entity a pointer to the associate entity instance.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit EntityDyingDelegate(IEntity* entity);

  ~EntityDyingDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter(const IGame& game) override;

  void Exit(const IGame& game) override;

  void Tick(const IGame& game, float delta) override;
};

}
