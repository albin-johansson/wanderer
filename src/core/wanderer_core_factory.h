#pragma once
#include "wanderer_core_impl.h"
#include "image_generator.h"

namespace albinjohansson::wanderer {

inline std::unique_ptr<IWandererCore> create_core(ImageGenerator& imageGenerator) {
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl(imageGenerator));
}

}
