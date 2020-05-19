#pragma once
#include "entity_state.h"

namespace wanderer {

class IEntity;

/**
 * The EntityDyingDelegate class is an implementation of IEntityState that is
 * meant to be used for delegating idle entity dying calls.
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

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void enter(const IWandererCore& core) override;

  void exit(const IWandererCore& core) override;

  void tick(const IWandererCore& core, float delta) override;
};

}  // namespace wanderer
