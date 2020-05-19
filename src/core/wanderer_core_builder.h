#pragma once

#include <texture_loader.h>

#include "wanderer_core.h"

namespace wanderer {

class WandererCoreBuilder {
 public:
  static SharedPtr<IWandererCore> build(ctn::TextureLoader& textureLoader);
};

}  // namespace wanderer
