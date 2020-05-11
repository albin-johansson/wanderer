#pragma once
#include <texture_loader.h>

#include "wanderer_core_impl.h"

namespace albinjohansson::wanderer {

inline std::shared_ptr<IWandererCore> create_core(
    ctn::TextureLoader& textureLoader)
{
  return std::shared_ptr<IWandererCore>(new WandererCoreImpl(textureLoader));
}

}  // namespace albinjohansson::wanderer
