#include "wanderer_controller_impl.h"

namespace albinjohansson::wanderer {

IWandererController_uptr CreateController() {
  return std::unique_ptr<IWandererController>(new WandererControllerImpl());
}

}