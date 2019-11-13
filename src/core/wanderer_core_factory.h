#pragma once
#include "wanderer_core_impl.h"
#include "image_generator.h"

namespace wanderer::core {

inline IWandererCore_uptr CreateCore(visuals::ImageGenerator_sptr imageGenerator) {
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl(std::move(imageGenerator)));
}

}
