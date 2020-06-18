#include <centurion.h>
#include <hints.h>

#include "application.h"

using centurion::Centurion;
using centurion::Log;

using namespace wanderer;

int main(int, char**)
{
  Centurion c;

  using namespace centurion::hint;
  set_hint<RenderDriver>(OpenGL);

  Log::set_priority(Log::Priority::Info);
  run();
  return 0;
}