#pragma once
#include "wanderer_core_impl.h"

namespace wanderer::core {

IWandererCore_uptr CreateCore() {
  return std::unique_ptr<IWandererCore>(new WandererCoreImpl());
}

}
