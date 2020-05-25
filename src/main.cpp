#include <centurion.h>

#include "application.h"

using namespace centurion;
using namespace wanderer;

static void run()
{
  Application app;
  app.run();
}

int main(int, char**)
{
  Centurion c;
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  Log::set_priority(Log::Priority::Info);
  run();
  return 0;
}