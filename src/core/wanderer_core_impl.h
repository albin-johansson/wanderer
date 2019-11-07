#pragma once
#include "wanderer_core.h"

namespace wanderer::core {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  WandererCoreImpl();

 public:
  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend IWandererCore_uptr CreateCore();

  ~WandererCoreImpl() override;

  void Update() override;

  void Render() override;
};

}
