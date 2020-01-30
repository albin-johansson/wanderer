#pragma once
#include <image_generator.h>
#include "wanderer_core_impl.h"

namespace albinjohansson::wanderer {

inline std::unique_ptr<IWandererCore> create_core(centurion::ImageGenerator& imageGenerator) {
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl(imageGenerator));
}

}
