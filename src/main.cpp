#include "centurion.h"
#include "wanderer_controller.h"
#include "wanderer_controller_factory.h"

using namespace centurion;
using namespace albinjohansson::wanderer;

static void run()
{
  auto controller = create_controller();
  controller->run();
}

int main(int, char**)
{
  const Centurion c;
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  run();
  return 0;
}