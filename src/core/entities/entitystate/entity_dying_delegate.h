#pragma once
#include "entity_state.h"
#include "entity.h"

namespace albinjohansson::wanderer {

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

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void Enter(const ILevel& level) override;

  void Exit(const ILevel& level) override;

  void Tick(const ILevel& level, float delta) override;
};

}
