#include "wanderer_controller_impl.h"

namespace wanderer::controller {

IWandererController_uptr CreateController() {
  return std::unique_ptr<IWandererController>(new WandererControllerImpl());
}

}