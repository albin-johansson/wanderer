#include "centurion.h"
#include "wanderer_controller.h"
#include "wanderer_controller_factory.h"

using namespace centurion;
using namespace albinjohansson::wanderer;

static void Run() {
  auto controller = create_controller();
  controller->run();
}

int main(int, char**) {
  Centurion c;
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  Run();
  return 0;
}