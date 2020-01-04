#include "wanderer_controller_impl.h"

namespace albinjohansson::wanderer {

std::unique_ptr<IWandererController> create_controller() {
  return std::unique_ptr<IWandererController>(new WandererControllerImpl());
}

}