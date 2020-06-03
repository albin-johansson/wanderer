#include <centurion.h>

#include "application.h"

using namespace centurion;
using namespace wanderer;

int main(int, char**)
{
  Centurion c;
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");  // TODO use new hint API

  Log::set_priority(Log::Priority::Info);
  run();
  return 0;
}