#include "wanderer_controller_impl.h"

namespace albinjohansson::wanderer {

std::unique_ptr<IWandererController> CreateController() {
  return std::unique_ptr<IWandererController>(new WandererControllerImpl());
}

}