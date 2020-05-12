#pragma once

#include <texture_loader.h>

#include "wanderer_core.h"

namespace albinjohansson::wanderer {

class WandererCoreBuilder {
 public:
  static Shared<IWandererCore> build(ctn::TextureLoader& textureLoader);
};

}  // namespace albinjohansson::wanderer
