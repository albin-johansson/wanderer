#include "wanderer_controller_impl.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

Unique<IWandererController> create_controller()
{
  return Unique<IWandererController>(new WandererControllerImpl());
}

}  // namespace albinjohansson::wanderer