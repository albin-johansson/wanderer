#pragma once
#include "wanderer_core.h"

namespace wanderer::core {

class WandererCoreImpl final : public IWandererCore {
 private:
  WandererCoreImpl();

 public:
  friend IWandererCore_uptr CreateCore();

  ~WandererCoreImpl() override;

  void Update() override;

  void Render() override;
};

}
