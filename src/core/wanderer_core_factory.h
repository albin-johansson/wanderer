#pragma once
#include "wanderer_core_impl.h"
#include "image_generator.h"

namespace albinjohansson::wanderer {

inline IWandererCore_uptr CreateCore(ImageGenerator& imageGenerator) {
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl(imageGenerator));
}

}
