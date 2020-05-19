#include "wanderer_controller_impl.h"
#include "wanderer_stdinc.h"

namespace wanderer {

UniquePtr<IWandererController> create_controller()
{
  return UniquePtr<IWandererController>(new WandererControllerImpl());
}

}  // namespace wanderer