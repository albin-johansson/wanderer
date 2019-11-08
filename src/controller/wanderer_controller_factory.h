#include "wanderer_controller_impl.h"

namespace wanderer::controller {

IWandererController_uptr CreateController(core::IWandererCore_uptr core) {
  return std::unique_ptr<IWandererController>(new WandererControllerImpl(std::move(core)));
}

}