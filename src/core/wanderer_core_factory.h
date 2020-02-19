#pragma once
#include <texture_loader.h>

#include "wanderer_core_impl.h"

namespace albinjohansson::wanderer {

inline std::unique_ptr<IWandererCore> create_core(
    centurion::video::TextureLoader& textureLoader)
{
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl(textureLoader));
}

}  // namespace albinjohansson::wanderer
