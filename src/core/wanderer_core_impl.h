#pragma once
#include "wanderer_core.h"
#include "vector_2.h"
#include "player.h"

namespace wanderer::core {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  IEntity_uptr player = nullptr;

  WandererCoreImpl();

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend IWandererCore_uptr CreateCore();

  void Update() override;

  void Render(view::Renderer& renderer) override;

  void SavePositions() override;

  void Interpolate(float alpha) override;
};

}
