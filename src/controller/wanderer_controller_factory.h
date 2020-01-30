#include "wanderer_controller_impl.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

unique<IWandererController> create_controller() {
  return unique<IWandererController>(new WandererControllerImpl());
}

}